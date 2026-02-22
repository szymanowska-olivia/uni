import pandas as pd
import matplotlib.pyplot as plt

files = [
    "euler_case1.csv",
    "verlet_case1.csv",
    "euler_case2.csv",
    "verlet_case2.csv",
    "euler_case3.csv",
    "verlet_case3.csv"
]

for file in files:
    df = pd.read_csv(file)
    
    plt.figure(figsize=(6,6))
    
    n_bodies = (len(df.columns) - 1) // 2
    
    for i in range(n_bodies):
        x_col = f"x{i}"
        y_col = f"y{i}"
        plt.plot(df[x_col], df[y_col], label=f"Ciało {i}")
    
    plt.axis('equal')  
    plt.xlabel("X [AU]")
    plt.ylabel("Y [AU]")
    plt.title(file)
    plt.legend()
    plt.grid(True)
    
    output_file = file.replace(".csv", ".png")
    plt.savefig(output_file)
    plt.close()
    
    print(f"Zapisano wykres do pliku: {output_file}")
