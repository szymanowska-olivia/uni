#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <cmath>
#include <limits.h>

using namespace std;


vector<int64_t> sieve(int64_t n){
    vector<bool> Prime(n + 1, true);
    vector<int64_t> p;

    Prime[0] = Prime[1] = false;

    for (int64_t i = 2; i * i <= n; i++) {
        if (Prime[i]) {
            for (int64_t j = i * i; j <= n; j += i) Prime[j] = false;
        }
    }
    for (int64_t i = 2; i<= n; i++) {
        if (Prime[i]) p.push_back(i);
    }
    return p;
}

vector<int64_t> rozklad(int64_t n, vector<int64_t> &p){ 
    vector<int64_t> v;
    if(n==0)v .push_back(0); 
    else if(n < 0) { 
        v.push_back(-1); 
        n *= -1;
    } else v.push_back(1);

    if(n < 2 && n > -2) return v;
    
    int64_t m = n;
    for (size_t i = 0; i < p.size() && p[i] * p[i] <= m; i++) {
        while (m % p[i] == 0){ 
            v.push_back(p[i]);
            m /= p[i];
        }
    }

    if(m > 1){
        /*
        for (int64_t i = p.back() + 2; i * i <= m; i += 2) {
            while (m % i == 0) {
                v.push_back(i);
                m /= i;
            }
        }
            */

        if (m>1) v.push_back(m);
    } 

    return v;
}

vector<int64_t> edgecase(){
    vector<int64_t> v;
    v.push_back(-1);
    for (int i = 0; i < 63; i++) v.push_back(2);
    return v;
}

int main(int argc, char *argv[]){
    if (argc < 2){
        cerr << "Blad: nie podano argumentow" << endl;
        return 1;
    }

    vector<int64_t> p = sieve(1000000); 

    for(int i = 1; i < argc; i++){
        int64_t n;
        try{
            n = stoll(argv[i]);
        } catch(invalid_argument &e){
            cerr << "Blad: " << e.what() << endl;
            return 1;
        }

        vector<int64_t> czynniki_pierwsze; 

        if (n == LLONG_MIN) czynniki_pierwsze = edgecase();
        else czynniki_pierwsze = rozklad(n, p);
        
        cout << n << " = ";
        for(size_t i = 0; i < czynniki_pierwsze.size() - 1; i++){
            cout << czynniki_pierwsze[i] << " * ";
        }
        cout << czynniki_pierwsze[czynniki_pierwsze.size() - 1] << endl;
    }
}
