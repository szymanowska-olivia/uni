/*
Dany jest ciąg N liczb całkowitych oraz Q zapytań składających się z dwóch liczb a i b.

Twoim zadaniem jest odpowiedzieć dla każdego zapytania jakie jest minimum na przedziale [a,b].
*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAX_N = 200000;
const int MAX_logN = log2(MAX_N);//buildign_cnt0

void preprocess_sparse_table(vector<vector<int>>& t, int N) {
    for (int i = 1; i <= log2(N); i++) {
        int dl = 1 << (i - 1);
        for (int j = 0; j + (1 << i) <= N; j++) {
            t[i][j] = min(t[i - 1][j], t[i - 1][j + dl]);
        }
    }
}

int sparse_table_min(int a, int b, const vector<vector<int>>& t) {
    a--;
    b--;
    int dl = b - a + 1;
    int k = log2(dl);
    return min(t[k][a], t[k][b - (1 << k) + 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<vector<int>> st(MAX_logN + 1, vector<int>(N));

    for (int i = 0; i < N; i++) {
        cin >> st[0][i];
    }

    preprocess_sparse_table(st, N);

    while (Q--) {
        int a, b;
        cin >> a >> b;
        cout << sparse_table_min(a, b, st) << "\n";
    }

}
