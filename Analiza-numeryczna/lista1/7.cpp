
#include <iostream>
#include <cmath>
#include <vector>

//dodawanie od najmniejszego

using namespace std;

const double x = (3.14159265358979323846) / 4;
const double W = 1e-16;   

int main() {
    vector<double> COSX;     
    double fact = 1, pow = 1, res = 1;
    int sgn = 1;
    int n = 1;

    COSX.push_back(res);

    double a;
    do {
        fact *= (2 * n - 1) * (2 * n);
        pow *= x * x;
        sgn *= -1;
        a = sgn * (pow / fact);
        res += a;
        COSX.push_back(res);
        n++;
    } while (abs(a) > W); 

    cout << "cos(x) " << cos(x) << endl;

    /*
    for (size_t i = 0; i < COSX.size(); i++) {
        cout << "wyraz " << i << " = " << COSX[i] << endl;
    }
    */

    cout << "COSX = " << res << endl;
}
