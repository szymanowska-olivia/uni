import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

N = 101
map = np.zeros((N, N))
mrowka = np.array([N//2, N//2]) 
STEPS = 10000
STEPS_PER_FRAME = 5000

k = 0  
v = np.array([(-1,0),(0,1),(1,0),(0,-1)])

def krok():
    global mrowka, k
    r, c = mrowka
    if map[r,c] == 0: #biale - w lewo
        k += 1
        k %= 4
        map[r,c] = 1
    else:   #czarne - w prawo
        k = (k - 1) % 4
        map[r,c] = 0
    x, y = v[k]
    x = (x + r)%N
    y = (y + c)%N
    mrowka = np.array([x, y])

fig, ax = plt.subplots()
im = ax.imshow(map, cmap='binary', vmin=0, vmax=1)
ax.set_xticks([]); ax.set_yticks([])
dot, = ax.plot([], [], 'ro', markersize=4)

def update(_):
    krok()
    im.set_data(map)
    dot.set_data([mrowka[1]], [mrowka[0]])
    return im, dot

anim = animation.FuncAnimation(fig, update, frames=100, interval=10, blit=True)
plt.show()
