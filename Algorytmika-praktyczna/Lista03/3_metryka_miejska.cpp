/*
W tym zadaniu będziemy posługiwali się metryką miejską, czyli odległość miedzy punktami a oraz b będziemy liczyli ze wzoru dist(a,b) = |xa−xb| + |ya−yb|.

Dane jest N punktów na płaszczyźnie. Twoim zadaniem jest ułożyć je w takiej kolejności p1, p2, …, pN, że suma dist(pi, pi+1) <= 2.1⋅10^9
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int BLOCK_SIZE = 1000;

bool compare(int a, int b, const vector<int>& x, const vector<int>& y) {
    int blockA = x[a - 1] / BLOCK_SIZE;
    int blockB = x[b - 1] / BLOCK_SIZE;
    if (blockA != blockB) return blockA < blockB;
    if (blockA % 2 == 0) return y[a - 1] < y[b - 1];
    return y[a - 1] > y[b - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    vector<int> x(N), y(N), idx(N);
    
    for (int i = 0; i < N; i++) {
        cin >> x[i] >> y[i];
        idx[i] = i + 1;
    }
    
    sort(idx.begin(), idx.end(), [&](int a, int b) { return compare(a, b, x, y);});
    
    for (int i = 0; i < N; ++i) cout << idx[i] << " ";
    cout << "\n";

}
