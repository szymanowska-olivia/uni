/*
Rotacją słowa T nazwiemy słowo, które można otrzymać ze słowa T poprzez wykonanie (może wielokrotnie) przełożenia litery z końca słowa na początek. Przykładowo, rotacjami słowa acab są słowa acab, baca, abac oraz caba.

Twoim zadaniem jest znalezienie minimalnej leksykograficznie rotacji słowa podanego na wejściu.
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const long long A1 = 911, M1 = 1000000007;
const long long A2 = 3571, M2 = 1000000009;

vector<long long> H1, H2;
vector<long long> A1_pow, A2_pow;

void preprocessing(const string& T) {
    int n = T.size();
    A1_pow[0] = A2_pow[0] = 1;

    for (int i = 1; i <= n; i++) {
        A1_pow[i] = (A1_pow[i-1] * A1) % M1;
        A2_pow[i] = (A2_pow[i-1] * A2) % M2;
    }

    for (int i = 0; i < n; i++) {
        H1[i+1] = (H1[i] * A1 + T[i]) % M1;
        H2[i+1] = (H2[i] * A2 + T[i]) % M2;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string T;
    cin >> T;
    int n = T.size();
    string S = T + T;

    H1.resize(S.size() + 1, 0);
    H2.resize(S.size() + 1, 0);
    A1_pow.resize(S.size() + 1, 0);
    A2_pow.resize(S.size() + 1, 0);

    preprocessing(S);

    int maxi = 0;
    for (int i = 1; i < n; i++) {
        int left = 0, right = n;
        while (left < right) {
            int mid = (left + right + 1) / 2;

            long long hash1_maxi = (H1[maxi + mid] - (H1[maxi] * A1_pow[mid]) % M1 + M1) % M1;
            long long hash1_i    = (H1[i + mid]    - (H1[i]    * A1_pow[mid]) % M1 + M1) % M1;

            long long hash2_maxi = (H2[maxi + mid] - (H2[maxi] * A2_pow[mid]) % M2 + M2) % M2;
            long long hash2_i    = (H2[i + mid]    - (H2[i]    * A2_pow[mid]) % M2 + M2) % M2;

            if (hash1_maxi == hash1_i && hash2_maxi == hash2_i) left = mid;
            else right = mid - 1;
        }
        if (left < n && S[i + left] < S[maxi + left]) maxi = i;
    }

    cout << S.substr(maxi, n) << '\n';
}
