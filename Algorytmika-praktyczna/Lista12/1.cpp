/*
Dane są dwa słowa T oraz P. Twoim zadaniem jest policzenie ile razy słowo P występuje w słowie T.
*/
#include <iostream>
#include <vector>
using namespace std;

const long long A1 = 911, M1 = 1000000007;
const long long A2 = 3571, M2 = 1000000009;

vector<long long> H1, H2;
vector<long long> A1_pow, A2_pow;
long long word1 = 0, word2 = 0;

void preprocessing (const string& T, const string& P){
    for (int i = 1; i <= T.size() + 1; i++) {
        A1_pow[i] = (A1_pow[i-1] * A1) % M1;
        A2_pow[i] = (A2_pow[i-1] * A2) % M2;
    }

    for (int i = 0; i < P.size(); i++) {
        word1 = (word1 * A1 + (P[i])) % M1;
        word2 = (word2 * A2 + (P[i])) % M2;
    }

    for (int i = 0; i < T.size(); i++) {
        H1[i+1] = (H1[i] * A1 + (T[i])) % M1;
        H2[i+1] = (H2[i] * A2 + (T[i])) % M2;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string T, P;
    cin >> T >> P;

    if (P.size() > T.size()) {
        cout << 0 << "\n";
        return 0;
    }

    H1.resize(T.size() + 1, 0);
    H2.resize(T.size() + 1, 0);
    A1_pow.resize(T.size() + 2, 1);
    A2_pow.resize(T.size() + 2, 1);

    preprocessing(T, P);

    int ile = 0;

    for (int i = 0; i <= T.size() - P.size(); i++) {
        long long curr1 = (H1[i + P.size()] + M1 - (H1[i] * A1_pow[P.size()]) % M1) % M1;
        long long curr2 = (H2[i + P.size()] + M2 - (H2[i] * A2_pow[P.size()]) % M2) % M2;

        if (curr1 == word1 && curr2 == word2) {
            ile++;
            //i += P.size() - 1;
        }
    }

    cout << ile << "\n";
}
