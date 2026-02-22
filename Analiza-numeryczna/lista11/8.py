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
N = len(t)

# =========================
# Iloczyn skalarny dyskretny
# =========================

def inner(p, q):
    return np.dot(p, q)

# =========================
# Rekurencja trójczłonowa
# =========================

max_n = 15
phi = []
alpha = np.zeros(max_n+1)
beta = np.zeros(max_n+1)

phi.append(np.ones(N))
phi.append(t.copy())

alpha[0] = inner(t * phi[0], phi[0]) / inner(phi[0], phi[0])

for k in range(1, max_n):
    alpha[k] = inner(t * phi[k], phi[k]) / inner(phi[k], phi[k])
    beta[k] = inner(phi[k], phi[k]) / inner(phi[k-1], phi[k-1])
    phi.append((t - alpha[k]) * phi[k] - beta[k] * phi[k-1])

# =========================
# Aproksymacje MNK
# =========================

tt = np.linspace(min(t), max(t), 1000)

plt.figure(figsize=(8,5))
plt.scatter(t, y, s=15, color="black", label="Dane")

for n in range(2, 16):
    w = np.zeros_like(tt)
    for k in range(n+1):
        ck = inner(y, phi[k]) / inner(phi[k], phi[k])
        w += ck * np.polyval(np.polyfit(t, phi[k], len(phi[k])-1), tt)

    plt.plot(tt, w, label=f"n={n}")

plt.title("Aproksymacja MNK – rekurencja trójczłonowa")
plt.legend(ncol=2, fontsize=8)
plt.grid()
plt.show()
