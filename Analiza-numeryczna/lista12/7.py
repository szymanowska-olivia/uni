import numpy as np

def newton_cotes_weights(n, a, b):
    """
    Oblicza wagi Newtona-Cotesa dla n+1 węzłów równoodległych na [a,b]
    """
    h = (b - a) / n
    A = np.zeros(n + 1)
    
    for k in range(n//2 + 1):  # tylko połowa wag, reszta przez symetrię
        # 1. Lista węzłów oprócz k
        nodes = [j for j in range(n+1) if j != k]
        
        # 2. Budujemy wielomian l_k(s) = ∏_{j≠k} (s - j)/(k - j)
        # Startujemy od wielomianu stopnia 0
        poly = np.array([1.0])
        for j in nodes:
            poly = np.convolve(poly, np.array([1.0, -j])) / (k - j) #mnożenie wielomianów 
        
        # 3. Obliczamy całkę ∫_0^n l_k(s) ds
        # Współczynniki wielomianu: poly[i] * s^i
        integral = sum(poly[i] * n**(i+1) / (i+1) for i in range(len(poly)))
        
        # 4. Waga
        A[k] = h * integral
        
        # 5. Symetria
        A[n - k] = A[k]
    
    return A

def QNC(f, a, b, n):
    """
    Oblicza kwadraturę Newtona-Cotesa rzędu n
    """
    h = (b - a) / n
    A = newton_cotes_weights(n, a, b)
    x_nodes = np.linspace(a, b, n + 1)
    fx = f(x_nodes)
    return np.sum(A * fx)

# --- Przykłady z zadania ---

# 1. ∫_{-1}^{9} sin(5x) dx
f1 = lambda x: np.sin(5*x)
Q1 = QNC(f1, -1, 9, n=10)  # przykład n=10
print("QNC for ∫_{-1}^{9} sin(5x) dx:", Q1)

# 2. ∫_{-1}^{1} 1/x dx   (uwaga: singularność w x=0!)  
# Możemy pominąć 0 lub wstawić n taki, aby węzły nie trafiały w 0
# np. n=6, węzły: -1, -0.6667, -0.3333, 0.3333, 0.6667, 1
f2 = lambda x: 1/x
Q2 = QNC(f2, -1, 1, n=6)
print("QNC for ∫_{-1}^{1} 1/x dx:", Q2)

# 3. ∫_{-7}^{1} dx / (1 + x^2)
f3 = lambda x: 1 / (1 + x**2)
Q3 = QNC(f3, -7, 1, n=10)
print("QNC for ∫_{-7}^{1} dx/(1+x^2):", Q3)
