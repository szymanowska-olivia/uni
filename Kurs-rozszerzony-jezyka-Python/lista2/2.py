
memo = {}

def sudan (n, x, y):
    if (n, x, y) in memo:
        return memo[(n, x, y)]
    
    if n == 0:
        return x + y
    if y == 0:
        return x
    
    a = sudan(n, x, y - 1)
    result = sudan(n - 1, a, a + y)

    memo[(n, x, y)] = result
    return result


n = 2 
x = 3 #bez memo x=2 i y=2
y = 2 #z memo x=3 i y=2

print("f_{0} ({1}, {2}) = {3}".format(n, x, y, sudan (n, x, y)))
