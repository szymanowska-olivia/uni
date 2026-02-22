#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

double f(double x) {
    return 3*x*x - 5*cos(7*x - 1);
}

double bisekcja(double a, double b, double tol = 1e-6) {
    double fa = f(a), fb = f(b);

    if (fa * fb > 0) {
        cerr << "Brak zmiany znaku dla a: " << a << " i b: " << b << endl;
        return NAN;
    }

    double m;
    while ((b - a) / 2.0 > tol) { 
        m = (a + b) / 2.0;
        double fm = f(m);

        if (fm == 0.0) m;
        else if (fa * fm < 0) b = m, fb = fm;
        else a = m, fa = fm;
    }
    return (a + b) / 2.0;
}

int main() {
    double l = -sqrt(5.0 / 3.0), r = sqrt(5.0 / 3.0), len = 0.01, a0 = l, b0 = a0 + len;

    while (b0 <= r) {
        if (f(a0) * f(b0) < 0) cout << bisekcja(a0, b0) << endl;
        a0 = b0;
        b0 += len;
    }

}
