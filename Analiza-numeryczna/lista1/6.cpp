#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int const W = 2e6;

int main(){
    vector<double> PI(W + 1, 0);

    PI[0] = 1;
    int poww = 1;
    for (int k = 1; k < W + 1; k++) {
        poww *= -1;
        PI[k] = PI[k-1] + (double)(poww/((2 * k) + 1));
    }

    cout << "PI" << endl;
    
    /*
    for (int i = 0; i < W + 1; i++) {
    cout << "wyraz " << i << " = " << 4 * PI[i] << endl;
    }
    */

    cout << "wyraz " << W << " = " << 4 * PI[W] << endl;

}