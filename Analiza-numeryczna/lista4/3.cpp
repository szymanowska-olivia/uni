#include <iostream>
#include <cmath>

using namespace std;

double f(double x) {
    return x - 0.49;
}

int main() {
    double a = 0.0, b = 1.0, alpha = 0.49; 
    double m, e_n, e;


    for (int n = 1; n <= 5; n++) {
        m = (a + b) / 2.0;           
        e_n = alpha - m;              
        e = (b - a) / 2.0;    

        cout << "f(" << n << ") a: " << a << " b: " << b << " m: " << m << " e_n: " << fabs(e_n) << " e: " << e << endl;

        if (f(a) * f(m) < 0) b = m; 
        else a = m; 
    }

}
