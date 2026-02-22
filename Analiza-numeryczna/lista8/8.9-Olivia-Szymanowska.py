import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

n = 4
M = 800
N_newton = 25
N_halley = 15
eps = 1e-6

def f(z):
    return z**n + 1

def df(z):
    return n * z**(n-1)

def ddf(z):
    return n * (n-1) * z**(n-2)

# pierwiastki równania z^n + 1 = 0
c = np.array([np.exp(1j * (np.pi + 2*np.pi*k) / n) for k in range(n)])

x = np.linspace(-1, 1, M)
y = np.linspace(-1, 1, M)
X, Y = np.meshgrid(x, y)
Z0 = X + 1j * Y

# metoda Newtona 
Z_newton = Z0.copy()
for _ in range(N_newton):
    Z_newton -= f(Z_newton)/df(Z_newton)

# odległości od wszystkich pierwiastków 
distances_newton = np.abs(Z_newton[..., np.newaxis] - c[np.newaxis, np.newaxis, :])
min_new = np.argmin(distances_newton, axis=2)
colors_newton = np.where(np.min(distances_newton, axis=2) < eps, min_new, -1)

# metoda Halleya
Z_halley = Z0.copy()
for _ in range(N_halley):
    Z_halley -= 1.0 / (df(Z_halley)/f(Z_halley) - 0.5 * ddf(Z_halley)/df(Z_halley))

distances_halley = np.abs(Z_halley[..., np.newaxis] - c[np.newaxis, np.newaxis, :])
min_hall = np.argmin(distances_halley, axis=2)
colors_halley = np.where(np.min(distances_halley, axis=2) < eps, min_hall, -1)

# kolory 
base_cmap = plt.get_cmap('tab10')
cmap = ListedColormap(['black'] + [base_cmap(i) for i in range(10)])
colors_newton_shifted = colors_newton + 1
colors_halley_shifted = colors_halley + 1

theta = np.linspace(0, 2*np.pi, 400)
unit_circle_x = np.cos(theta)
unit_circle_y = np.sin(theta)

fig, axes = plt.subplots(1, 2, figsize=(12, 6))

for ax, colors, title in zip(
    axes,
    [colors_newton_shifted, colors_halley_shifted],
    ['Metoda Newtona', 'Metoda Halleya']
):
    im = ax.imshow(colors, extent=(-1,1,-1,1), origin='lower', cmap=cmap)
    ax.plot(unit_circle_x, unit_circle_y, 'k--', linewidth=1)
    ax.scatter(c.real, c.imag, c='white', edgecolors='black', s=80, zorder=5)
    
    for k, root in enumerate(c):
        ax.text(root.real + 0.05, root.imag + 0.05, rf'$\zeta_{{{k+1}}}$',
                color='black', fontsize=10, zorder=6)
    
    ax.set_title(title)
    ax.set_xlabel('Re(z)')
    ax.set_ylabel('Im(z)')
    ax.set_aspect('equal')

plt.suptitle(f'Baseny zbieżności dla równania $z^{{{n}}} + 1 = 0$', fontsize=14)
plt.tight_layout()
plt.show()
