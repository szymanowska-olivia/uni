#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

float f(float x){
    float res = (162 * (1 - cos(5 * x))) / (x * x);
    return res;
}

double f2(double x){
    return (162 * (1 - cos(5 * x))) / (x * x);
} 

int main(){
    vector<float> pow(21, 1);
    vector<double> pow2(21, 1);

    float wartosc = 1;
    double wartosc2 = 1;

    for (int i = 1; i < 21; i++) {
        wartosc /= 10;
        wartosc2 /= 10;

        pow[i] = wartosc;
        pow2[i] = wartosc2;
    }

    cout << "pojedyncza precyzja" << endl;
    for (int i = 11; i < 21; i++) {
    cout << "f(10^" << i << ") = " << f(pow[i]) << " ";
    }

    cout << endl;

    cout << "podwojna precyzja" << endl;
    for (int i = 11; i < 21; i++) {
    cout << "f(10^" << i << ") = " << f2(pow2[i]) << " ";
    }

   // cout << " efwf " << f(0.00001) << " " << f2(0.00001) << endl;

}