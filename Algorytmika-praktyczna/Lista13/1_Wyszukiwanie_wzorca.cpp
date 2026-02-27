/*
Dane są dwa słowa T oraz P. Twoim zadaniem jest policzenie ile razy słowo P występuje w słowie T.
*/
#include <iostream>
#include <vector>

using namespace std;

string T;
vector<int> ps;
int ile = 0;

void prefikso_suffiksy(int w){
    int idx, pom;
    for(int i = 1; i < T.size(); i++){
        idx = ps[i - 1]; //indeks kolejnej litery prefiksu ostatniego prefikso-suffiksu
        while(idx > 0 && T[idx] != T[i]) idx = ps[idx - 1];
        if (T[idx] == T[i]) idx++;

        ps[i] = idx;
        if (ps[i] == w) ile++;
        /* sprawdzamy wszystkie prefikso-suffiksy prefikso-suffiksow 
        az ktorys nie bedzie pasowal/sprawdzimy wszystkie i czy litera jest nim sama w sobie*/
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string S;
    cin >> S;
    cin >> T;

    int wzorzec_dł = T.size();

    T+='#';
    T+=S;

    ps.resize(T.size(), 0);
    prefikso_suffiksy(wzorzec_dł);

    cout << ile << "\n";
}