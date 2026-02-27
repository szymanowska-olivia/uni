/*
Dany jest ciąg N liczb całkowitych oraz Q zapytań składających się z dwóch liczb a i b.

Twoim zadaniem jest odpowiedzieć dla każdego zapytania jakie jest minimum na przedziale [a,b].
*/
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

const int MAX_N = 200000;

int N, Q, leftMin[MAX_N], rightMin[MAX_N];
vector<int> x, mini;
vector<pair<int, int>> q;

void divide(int l, int r, vector<int> qIdx) {
    if (qIdx.empty()) return;

    if (l == r) {
        for (uint64_t i = 0; i < qIdx.size(); i++){
            int idx = qIdx[i];
            mini[idx] = x[l];
        }
        return;
    }

    int m = (l + r) / 2;
    vector<int> leftQueries, rightQueries;

    leftMin[m] = x[m];
    for (int i = m - 1; i >= l; i--) leftMin[i] = min(x[i], leftMin[i + 1]);

    rightMin[m + 1] = x[m + 1];
    for (int i = m + 2; i <= r; i++) rightMin[i] = min(rightMin[i - 1], x[i]);

   

    for (uint64_t i = 0; i < qIdx.size(); i++) {
        int idx = qIdx[i]; 
        int a = q[idx].first, b = q[idx].second;
        
        if (a <= m && m < b) mini[idx] = min({leftMin[a], x[m], rightMin[b]});
        else if (b <= m) leftQueries.push_back(idx);
        else rightQueries.push_back(idx);
    }
    

    divide(l, m, leftQueries);
    divide(m + 1, r, rightQueries);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    x.resize(N);
    mini.resize(Q);
    q.resize(Q);
    vector<int> qIdx;

    for (int i = 0; i < N; i++) cin >> x[i];
    for (int i = 0; i < Q; i++) {
        cin >> q[i].first >> q[i].second;
        q[i].first--;
        q[i].second--;
        qIdx.push_back(i);
    }
    
    divide(0, N - 1, qIdx);

    for (int i = 0; i < Q; i++) cout << mini[i] << "\n";

}
