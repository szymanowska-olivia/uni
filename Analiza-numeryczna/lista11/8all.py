import numpy as np
import matplotlib.pyplot as plt

def f(t):
    return 2.14 * (t + 1.4) * (t + 5.3) * (t - 0.44)

data = np.loadtxt("punkty.csv", delimiter=",")
t = data[:, 0]
y = data[:, 1]

idx = np.argsort(t)
t = t[idx]
y = y[idx]

t_plot = np.linspace(min(t), max(t), 1000)

# interpolacja newtona
def divided_differences(x, y):
    n = len(x)
    coef = y.astype(float).copy()
    for j in range(1, n):
        for i in range(n - 1, j - 1, -1):
            coef[i] = (coef[i] - coef[i - 1]) / (x[i] - x[i - j])
    return coef

def newton_poly(coef, x_nodes, x):
    p = coef[-1]
    for k in range(len(coef) - 2, -1, -1):
        p = p * (x - x_nodes[k]) + coef[k]
    return p

coef_newton = divided_differences(t, y)
y_newton = newton_poly(coef_newton, t, t_plot)

# aproksymacja sredniokwadratrowa
def orthogonal_polynomials(t, n):
    P = []
    norms = []

    # p0
    p0 = np.ones_like(t)
    P.append(p0)
    norms.append(np.dot(p0, p0))

    # p1
    alpha0 = np.dot(t * p0, p0) / norms[0]
    p1 = (t - alpha0) * p0
    P.append(p1)
    norms.append(np.dot(p1, p1))

    for k in range(1, n):
        alpha = np.dot(t * P[k], P[k]) / norms[k]
        beta = norms[k] / norms[k - 1]
        pk1 = (t - alpha) * P[k] - beta * P[k - 1]
        P.append(pk1)
        norms.append(np.dot(pk1, pk1))

    return P, norms


def least_squares_orthogonal(t, y, n, t_plot):

    P, norms = orthogonal_polynomials(t, n)

    # współczynniki aproksymacji
    coeffs = [np.dot(y, P[k]) / norms[k] for k in range(n + 1)]

    # wartości wielomianów w punktach wykresu
    P_plot = [np.ones_like(t_plot)]
    if n >= 1:
        alpha0 = np.dot(t * P[0], P[0]) / norms[0]
        P_plot.append((t_plot - alpha0))

    for k in range(1, n):
        alpha = np.dot(t * P[k], P[k]) / norms[k]
        beta = norms[k] / norms[k - 1]
        pk1 = (t_plot - alpha) * P_plot[k] - beta * P_plot[k - 1]
        P_plot.append(pk1)

    # składanie wielomianu
    w = np.zeros_like(t_plot)
    for k in range(n + 1):
        w += coeffs[k] * P_plot[k]

    return w

fig, axs = plt.subplots(2, 2, figsize=(14, 10))

# A
axs[0, 0].plot(t_plot, f(t_plot), label="f(t)", linewidth=2)
axs[0, 0].scatter(t, y, color="red", s=15, label="Dane pomiarowe")
axs[0, 0].set_title("(a) Funkcja f(t) i zbiór D")
axs[0, 0].legend()
axs[0, 0].grid(True)

# b
axs[0, 1].plot(t_plot, y_newton, color="green", label="Interpolacja Newtona")
axs[0, 1].scatter(t, y, color="red", s=15, label="Dane")
axs[0, 1].set_title("(b) Wielomian interpolacyjny Newtona")
axs[0, 1].legend()
axs[0, 1].grid(True)

# c
for n in range(2, 16):
    y_approx = least_squares_orthogonal(t, y, n, t_plot)
    axs[1, 0].plot(t_plot, y_approx, label=f"n={n}")

axs[1, 0].scatter(t, y, color="black", s=10, label="Dane")
axs[1, 0].set_title("(c) Aproksymacja średniokwadratowa")
axs[1, 0].legend(ncol=2, fontsize=8)
axs[1, 0].grid(True)

axs[1, 1].axis("off")

plt.tight_layout()
plt.show()
