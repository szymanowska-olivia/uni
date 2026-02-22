import numpy as np
import matplotlib.pyplot as plt

def de_casteljau(points, t):
    pts = points.copy()
    n = len(pts)

    for r in range(1, n):
        for i in range(n - r):
            pts[i] = (1 - t) * pts[i] + t * pts[i + 1]

    return pts[0]

def rational_bezier_casteljau(control_points, weights, num_points=300):
    # (wx, wy, w)
    points_w_weight = np.array([
        [w * x, w * y, w]
        for (x, y), w in zip(control_points, weights)
    ])

    t_values = np.linspace(0, 1, num_points)
    curve = np.zeros((num_points, 2))

    for i, t in enumerate(t_values):
        X, Y, W = de_casteljau(points_w_weight, t)
        curve[i] = [X / W, Y / W]

    return curve

control_points = np.array([
    [39.5, 10.5],
    [30, 20],
    [6, 6],
    [13, -12],
    [63, -12.5],
    [18.5, 17.5],
    [48, 63],
    [7, 25.5],
    [48.5, 49.5],
    [9, 19.5],
    [48.5, 35.5],
    [59, 32.5],
    [56, 20.5]
])

weights = np.array([
    1, 2, 3, 2.5, 6, 1.5, 5,
    1, 2, 1, 3, 5, 1
])

curve = rational_bezier_casteljau(control_points, weights)

plt.figure(figsize=(10, 8))
plt.plot(curve[:, 0], curve[:, 1], 'r', linewidth=2,
         label='Wymierna krzywa Beziera')
#plt.plot(control_points[:, 0], control_points[:, 1], 'bo--',
#        label='Punkty kontrolne')

plt.axis('equal')
plt.grid(True)
plt.legend()
plt.title("Wymierna krzywa Beziera")
plt.show()
