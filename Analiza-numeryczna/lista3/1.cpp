#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.141592653589793;
const double W = 1e-16;   


int main(){
    double x = -2134; //-100

    cout <<"a) " << "utrata cyfr znaczących" << endl;
    cout << (pow(x, 3) + sqrt(pow(x, 6) + 2025)) << endl;
    cout <<"a) " << "lepsze" << endl;
    cout << (2025.0 / (pow(x, 3) - sqrt(pow(x, 6) + 2025))) << endl;

    double y = 1e-8; // 1e-6

    double mian = 1, pow_y = y, res = 0;
    int sgn = 1;


    double a;
    do {
        mian += 2;
        pow_y *= y * y;
        sgn *= -1;
        a = sgn * (pow_y / mian);
        res += a;
    } while (res + a != res); 

    cout <<"b) " << "utrata cyfr znaczących" << endl;
    cout << (pow(y, -3) * (atan(y) - y)) << endl;
    cout <<"b) " << "lepsze" << endl;
    cout << (pow(y, -3) *(res)) << endl;


}