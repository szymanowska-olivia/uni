#include <iostream>
#include <cmath>

using namespace std;

const int k = 30; // 0 w res pojawia sie przy k = 30

double f(int k){

    if (k == 1) return 2.0;

    double pot = pow(2, k - 1);
    double poww = (f(k - 1) / pot) * (f(k - 1) / pot);

    double res = 
    pot * sqrt(2 * (1 - sqrt(1 - (poww))));

    double res2 = 
    pot * sqrt(2 * (((poww) / (1 + sqrt(1 - poww)))));

    return res;
}


int main(){


    cout << f(k) << endl;
}