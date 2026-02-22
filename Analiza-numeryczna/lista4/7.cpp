#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int newton(double a, double x0, double eps = 1e-12, int maxIter = 50) {
    double x = x0;
    double og = sqrt(a);

    for (int i = 1; i <= maxIter; ++i) {
        x = 0.5 * (x + a / x);
        double e = fabs((x - og) / og);
        if (e < eps) {
            cout << "m: " << a << " x_0: " << x0 << " x_" << i << " = " << x << "\n";
            return i;
        }
    }
    cout << "m: " << a << " x_0: " << x0 << " x_" << maxIter << " = " << x << "\n";
    return maxIter;
}

int main() {
    vector<double> m_i = {0.5, 0.75, 0.9, 0.99};
    vector<int> c_i = {-5, -2, 0, 3, 6, 10};
    vector<double> x0_i = {0.5, 1.0, 2.0};

    for (double m : m_i) {
        for (int c : c_i) {
            for (double x0 : x0_i) {
                double sqrt_a = 0;
                if (c%2 == 0) sqrt_a = newton(m, x0) * pow(2.0, c / 2.0);
                else sqrt_a = newton(m * 2, x0) * pow(2.0, c / 2.0);
                double a = m * pow(2.0, c);
                cout << "m: " << m << "  c: " << c  << "  x0: " << x0 << "  sqrt(a) ≈ " << sqrt_a << "  blad: " << fabs(sqrt_a - sqrt(a)) << endl;
            }
            cout << endl;
        }
    }

}