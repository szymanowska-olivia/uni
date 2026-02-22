#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int newton(double a, double x0, double eps = 1e-12, int maxIter = 50) {
    double x = x0;
    double og = 1.0 / sqrt(a);

    for (int i = 1; i <= maxIter; ++i) {
        x = 0.5 * x * (3.0 - a * x * x);
        double e = fabs((x - og) / og);
        if (e < eps) {
            cout << "a: " << a << " x_0: " << x0 << " x_" << i << " = " << x << "\n";
            return i;
        }
    }
    cout << "a: " << a << " x_0: " << x0 << " x_" << maxIter << " = " << x << "\n";
    return maxIter;
}

int main() {
    vector<double> valuesA = {0.01, 0.1, 1.0, 10.0, 100.0};
    vector<double> starts  = {0.1, 1.0, 10.0};

    for (size_t i = 0; i < valuesA.size(); ++i) {
        double a = valuesA[i];
        for (size_t j = 0; j < starts.size(); ++j) {
            double x0 = starts[j];
            newton(a, x0);
        }
        cout << endl;
    }
}