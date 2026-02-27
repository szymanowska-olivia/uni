/*
Dane jest słowo T. Twoim zadaniem jest znalezienie najdłuższego (spójnego) podsłowa słowa T, które jest palindromem.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const long long A1 = 911, M1 = 1000000007;
const long long A2 = 3571, M2 = 1000000009;

vector<long long> H1, H2, RH1, RH2;
vector<long long> A1_pow, A2_pow;

void preprocessing(const string& T, const string& R) {
    int n = T.size();
    A1_pow[0] = A2_pow[0] = 1;

    for (int i = 1; i <= n; i++) {
        A1_pow[i] = (A1_pow[i-1] * A1) % M1;
        A2_pow[i] = (A2_pow[i-1] * A2) % M2;
    }

    for (int i = 0; i < n; i++) {
        H1[i+1] = (H1[i] * A1 + T[i]) % M1;
        H2[i+1] = (H2[i] * A2 + T[i]) % M2;
        RH1[i+1] = (RH1[i] * A1 + R[i]) % M1;
        RH2[i+1] = (RH2[i] * A2 + R[i]) % M2;
    }
}

pair<long long, long long> get_hash(const vector<long long>& H1, const vector<long long>& H2, int l, int r) {
    long long hash1 = (H1[r] - (H1[l] * A1_pow[r - l]) % M1 + M1) % M1;
    long long hash2 = (H2[r] - (H2[l] * A2_pow[r - l]) % M2 + M2) % M2;
    return {hash1, hash2};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string T;
    cin >> T;
    int n = T.size();
    string R = T;
    reverse(R.begin(), R.end());

    H1.resize(n+1, 0); H2.resize(n+1, 0);
    RH1.resize(n+1, 0); RH2.resize(n+1, 0);
    A1_pow.resize(n+1, 0); A2_pow.resize(n+1, 0);

    preprocessing(T, R);

    int best_len = 0, best_pos = 0;

    for (int center = 0; center < n; center++) {
        //np
        int l = 0, r = min(center, n - center - 1) + 1;
        while (l < r) {
            int mid = (l + r) / 2;
            auto hash_L = get_hash(H1, H2, center - mid, center + mid + 1);
            auto hash_R = get_hash(RH1, RH2, n - (center + mid + 1), n - (center - mid));
            if (hash_L == hash_R) l = mid + 1;
            else r = mid;
        }
        l--;
        int len = 2 * l + 1;
        if (len > best_len) {
            best_len = len;
            best_pos = center - l;
        }

        //parzysta 
        l = 0; r = min(center + 1, n - center - 1) + 1;
        while (l < r) {
            int mid = (l + r) / 2;
            auto hash_L = get_hash(H1, H2, center - mid + 1, center + mid + 1);
            auto hash_R = get_hash(RH1, RH2, n - (center + mid + 1), n - (center - mid + 1));
            if (hash_L == hash_R) l = mid + 1;
            else r = mid;
        }
        l--;
        len = 2 * l;
        if (len > best_len) {
            best_len = len;
            best_pos = center - l + 1;
        }
    }

    cout << T.substr(best_pos, best_len) << '\n';
}
