import numpy as np

def weights(n):
    A = np.zeros(n+1)
    
    for k in range(n//2 + 1):  
        # węzły bez k
        nodes = [j for j in range(n+1) if j != k]
        
        # wielomian stopnia 0
        poly = np.array([1.0])
        for j in nodes:
            poly = np.convolve(poly, np.array([1.0, -j])) / (k - j)
        
        # suma c_i * n^(i+1)/(i+1)
        integral = np.sum(poly * np.array([n**(i+1)/(i+1) for i in range(len(poly))]))
        
        A[k] = integral
        A[n - k] = integral  
    
    return A

def QNC(f, a, b, n):
    h = (b - a) / n
    A = weights(n) * h
    x = np.linspace(a, b, n+1)
    fx = f(x)
    return np.sum(A * fx)

def f1(x): return np.sin(5*x)
def f2(x): return 1/x
def f3(x): return 1/(1+x**2)

print("QNC ∫_{-1}^{9} sin(5x) dx:")
for n in range(2, 36):
    print("n =",n,":", QNC(f1, -1, 9, n))

print("\nQNC ∫_{1}^{5} 1/x dx:")
for n in range(2, 36):
    print("n =",n,":", QNC(f2, 1, 5, n))

print("\nQNC ∫_{-7}^{1} dx/(1+x^2):")
for n in range(2, 36):
    print("n =",n,":", QNC(f3, -7, 1, n))
