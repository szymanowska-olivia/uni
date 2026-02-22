#include <iostream>
#include <cmath>

using namespace std;

const double x = 0.01;

int main(){

    double pot = pow(x, 15);
    double res = ((sqrt(12150 * pot + 9) - 3) / pot); //zle
    double res2 = ((12150) / (sqrt(12150 * pot + 9) + 3)); 

    cout << "bledne: "<< res << " poprawne: "<< res2 << endl;
}