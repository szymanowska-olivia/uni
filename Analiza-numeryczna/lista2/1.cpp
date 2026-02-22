#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<double> v;

    int mantissa_bits = 4;
    int max_mantissa = 1 << mantissa_bits; 
    double exponents[3] = {0.5, 1.0, 2.0};

    for (int m = 0; m < max_mantissa; m++) {
        double mant = 0.5 + m / 32.0; 
        for (double exp : exponents) {
            double res = mant * exp;
            v.push_back(res);
            v.push_back(-res);
        }
    }

    sort(v.begin(), v.end());

    for (double x : v)
        cout << x << endl;

}
