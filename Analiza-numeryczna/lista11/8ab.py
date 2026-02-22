import numpy as np
import matplotlib.pyplot as plt
import csv

# =========================
# Funkcja teoretyczna
# =========================

def f(t):
    return 2.14 * (t + 1.4) * (t + 5.3) * (t - 0.44)

# =========================
# Wczytywanie danych
# =========================

def load_csv(filename):
    t, y = [], []
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            try:
                t.append(float(row[0]))
                y.append(float(row[1]))
            except:
                continue
    return np.array(t), np.array(y)

t, y = load_csv("punkty.csv")

# sortowanie
idx = np.argsort(t)
t = t[idx]
y = y[idx]

N = len(t)
tt = np.linspace(min(t), max(t), 1000)

# =========================
# (a) wykres f i danych
# =========================

plt.figure(figsize=(8,5))
plt.plot(tt, f(tt), label="f(t)", linewidth=2)
plt.scatter(t, y, s=15, color="red", label="Dane pomiarowe")
plt.legend()
plt.title("(a) Funkcja f i zbiór D")
plt.grid()
plt.show()

# =========================
# (b) Newton – TABLICA ILORAZÓW
# =========================

def divided_difference_table(t, y):
    n = len(t)
    table = np.zeros((n, n))
    table[:,0] = y
    for j in range(1, n):
        for i in range(n-j):
            table[i,j] = (table[i+1,j-1] - table[i,j-1]) / (t[i+j] - t[i])
    return table[0]

coef = divided_difference_table(t, y)

def newton_eval(x, t, coef):
    result = coef[0]
    product = 1.0
    for k in range(1, len(coef)):
        product *= (x - t[k-1])
        result += coef[k] * product
    return result

# liczymy punkt po punkcie (STABILNIE)
p_vals = np.array([newton_eval(x, t, coef) for x in tt])

plt.figure(figsize=(8,5))
plt.scatter(t, y, s=15, color="red", label="Dane")
plt.plot(tt, p_vals, color="green",
         label="Wielomian interpolacyjny (Newton)")
plt.legend()
plt.title("(b) Wielomian interpolacyjny stopnia 105 – Newton")
plt.grid()
plt.show()
