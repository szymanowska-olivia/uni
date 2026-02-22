#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main(){
    vector<float> Yn(51, 0);
    vector<double> Yn2(51, 0);

    Yn[0] = 1;
    Yn[1] = -1/9;
    Yn2[0] = 1;
    Yn2[1] = -1/9;

    for (int i = 2; i < 51; i++) {
        Yn[i] = (float)(98/9) * Yn[i-1] + (float)(11/9) * Yn[i-2];
        Yn2[i] = (double)(98/9) * Yn2[i-1] + (double)(11/9) * Yn2[i-2];
    }

    cout << "pojedyncza precyzja" << endl;
    for (int i = 0; i < 51; i++) {
    cout << "y_" << i << " = " << Yn[i] << endl;
    }

    cout << endl;

    cout << "podwojna precyzja" << endl;
    for (int i = 0; i < 51; i++) {
    cout << "y_" << i << " = " << Yn2[i] << endl;
    }

   // cout << " efwf " << f(0.00001) << " " << f2(0.00001) << endl;

}