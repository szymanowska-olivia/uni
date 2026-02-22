#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main(){
    vector<double> In(21, 0);

    In[0] = log(2026) - log(2025);

    for (int i = 1; i < 21; i++) 
        In[i] = (1/i) - (2025 * In[i-1]);
    

    cout << "I_1,I_3,...I_19" << endl;
    for (int i = 1; i < 21; i+=2) {
    cout << "I_" << i << " = " << In[i] << endl;
    }

    cout << endl;

    cout << "I_2,I_4,...I_20" << endl;
    for (int i = 2; i < 21; i+=2) {
    cout << "I_" << i << " = " << In[i] << endl;
    }

   // cout << " efwf " << f(0.00001) << " " << f2(0.00001) << endl;

}