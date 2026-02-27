/*
Prefikso-sufiksem słowa T nazwiemy słowo, które jest zarówno prefiksem jak i sufiksem słowa T, ale nie jest ani puste, ani całym słowem T. Przykładowo, prefikso-sufiksami słowa abcababcab są słowa ab oraz abcab.

Twoim zadaniem jest znalezienie długości wszystkich prefikso-sufiksów słowa podanego na wejściu.
*/
#include <iostream>
#include <vector>

using namespace std;

string T;
vector<int> ps;

void prefikso_suffiksy(){
    int idx, pom;
    for(int i = 1; i < T.size(); i++){
        idx = ps[i - 1]; //indeks kolejnej litery prefiksu ostatniego prefikso-suffiksu
        while(idx > 0 && T[idx] != T[i]) idx = ps[idx - 1];
        if (T[idx] == T[i]) idx++;

        ps[i] = idx;
        /* sprawdzamy wszystkie prefikso-suffiksy prefikso-suffiksow 
        az ktorys nie bedzie pasowal/sprawdzimy wszystkie i czy litera jest nim sama w sobie*/
    }
}

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    ps.resize(T.size(), 0);

    prefikso_suffiksy();

    int i = T.size() - 1;

    vector<int> res;
    while(1){
        if(ps[i] == 0) break;
        res.push_back(ps[i]);
        int pom = ps[i];
        i = pom - 1;
    }
    /*
    for (int j = 0; j < T.size(); j++) cout << ps[j] << " ";
   cout << "\n";
    */
   for (int j = res.size() - 1; j > -1; j--) cout << res[j] << " ";
   cout << "\n";

}