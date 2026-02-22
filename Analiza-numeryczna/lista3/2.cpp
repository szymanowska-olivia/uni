#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.141592653589793;

int main(){
    double x, a = 1, b = 1e8, c = 1e-8;

    cout <<"x1 " << "utrata cyfr znaczących" << endl;
    cout << ((sqrt((b * b) - (4 * a * c)) - b) / (2 * a)) << endl;
    cout <<"x1 " << "lepsze" << endl;
    cout << ((-1) * (2 * c) / ((b * b) + sqrt((b * b) - (4 * a * c)))) << endl;


    cout <<"x2 " << "utrata cyfr znaczących" << endl;
    cout << (( -1 * sqrt((b * b) - (4 * a * c)) - b) / (2 * a)) << endl;
    cout <<"x2 " << "lepsze (takie same)" << endl;
    cout << (( -1 * sqrt((b * b) - (4 * a * c)) - b) / (2 * a)) << endl;


}