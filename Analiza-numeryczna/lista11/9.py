import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import savgol_filter

# === 1. Wczytanie i przygotowanie danych ===
filename = "dane.csv"
df = pd.read_csv(filename, encoding="utf-8")

num_cols = ['Nowe zgony', 'Nowe wyzdrowienia', 'Zmiana liczby aktywnych przypadków']
df = df.replace({r'\xa0': ''}, regex=True)
for col in num_cols:
    df[col] = pd.to_numeric(df[col], errors='coerce').fillna(0)

df['Zmiana aktywnych'] = df['Zmiana liczby aktywnych przypadków'].diff().fillna(0)
df['Data'] = pd.to_datetime(df['Data'], dayfirst=True)
dates = df['Data']

# === 2. Wygładzanie danych ===
# Rolling (dla porównania)
df['Zmiana aktywnych rolling'] = df['Zmiana aktywnych'].rolling(7, center=True).mean()

# Savitzky–Golay (DO MODELI)
window = 15   # nieparzyste
poly = 3

df['Nowe zgony smooth'] = savgol_filter(df['Nowe zgony'], window, poly)
df['Nowe wyzdrowienia smooth'] = savgol_filter(df['Nowe wyzdrowienia'], window, poly)
df['Zmiana aktywnych smooth'] = savgol_filter(df['Zmiana aktywnych'], window, poly)

# === 3. Funkcje pomocnicze ===
def create_lag_matrix(series, lag=3):
    X, y = [], []
    for i in range(lag, len(series)):
        X.append([series[i-j-1] for j in range(lag)])
        y.append(series[i])
    return np.array(X), np.array(y)

def linear_regression_mnk(X, y):
    X_ = np.hstack([np.ones((X.shape[0],1)), X])
    beta = np.linalg.inv(X_.T @ X_) @ X_.T @ y
    return beta

def clenshaw(x, coefs):
    b_next = 0
    b_curr = 0
    for i in range(len(coefs)-1, 0, -1):
        b_prev = b_curr
        b_curr = coefs[i] + 2*x*b_curr - b_next
        b_next = b_prev
    return coefs[0] + x*b_curr - b_next

def check_stability(beta):
    coeffs = [1, -beta[1], -beta[2], -beta[3]]
    roots = np.roots(coeffs)
    return roots

# === 4. WYKRES PORÓWNAWCZY RAW / ROLLING / SAVITZKY ===
plt.figure(figsize=(12,6))
plt.plot(dates, df['Zmiana aktywnych'], alpha=0.3, label='Raw')
plt.plot(dates, df['Zmiana aktywnych rolling'], linewidth=2, label='Rolling (7)')
plt.plot(dates, df['Zmiana aktywnych smooth'], linewidth=2, label='Savitzky–Golay')
plt.title("Porównanie metod wygładzania – zmiana aktywnych")
plt.legend()
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()

# === 5. Rekurencja trójczłonowa ===
fig1, ax1 = plt.subplots(figsize=(12,6))
for col, label in zip(
    ['Nowe zgony smooth', 'Nowe wyzdrowienia smooth', 'Zmiana aktywnych smooth'],
    ['Zgony','Wyzdrowienia','Zmiana aktywnych']
):
    X, y = create_lag_matrix(df[col])
    beta = linear_regression_mnk(X, y)
    y_pred = np.hstack([np.ones((X.shape[0],1)), X]) @ beta
    ax1.plot(dates[3:], y_pred, label=label)

    roots = check_stability(beta)
    print(f"\n{label} – pierwiastki rekurencji:", roots)
    print("Moduły:", np.abs(roots))

ax1.set_title("Rekurencja trójczłonowa (Savitzky–Golay)")
ax1.legend()
plt.xticks(rotation=45)

# === 6. MNK liniowy ===
fig2, ax2 = plt.subplots(figsize=(12,6))
t = np.arange(len(df))

for col, label in zip(
    ['Nowe zgony smooth', 'Nowe wyzdrowienia smooth', 'Zmiana aktywnych smooth'],
    ['Zgony','Wyzdrowienia','Zmiana aktywnych']
):
    X = t.reshape(-1,1)
    beta = linear_regression_mnk(X, df[col].values)
    y_pred = np.hstack([np.ones((len(t),1)), X]) @ beta
    ax2.plot(dates, y_pred, label=label)

ax2.set_title("MNK liniowy (Savitzky–Golay)")
ax2.legend()
plt.xticks(rotation=45)

# === 7. Czebyszew + Clenshaw ===
fig3, ax3 = plt.subplots(figsize=(12,6))
degree = 8
t_norm = 2*(t - t.min())/(t.max() - t.min()) - 1

for col, label in zip(
    ['Nowe zgony smooth', 'Nowe wyzdrowienia smooth', 'Zmiana aktywnych smooth'],
    ['Zgony','Wyzdrowienia','Zmiana aktywnych']
):
    y = df[col].values
    T = np.ones((len(t_norm), degree+1))
    T[:,1] = t_norm
    for k in range(2, degree+1):
        T[:,k] = 2*t_norm*T[:,k-1] - T[:,k-2]

    coefs = np.linalg.inv(T.T @ T) @ T.T @ y
    y_pred = np.array([clenshaw(xi, coefs) for xi in t_norm])
    ax3.plot(dates, y_pred, label=label)

ax3.set_title("Czebyszew + Clenshaw (Savitzky–Golay)")
ax3.legend()
plt.xticks(rotation=45)

plt.tight_layout()
plt.show()
