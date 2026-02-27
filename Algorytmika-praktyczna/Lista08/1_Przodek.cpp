/*
Dane jest drzewo ukorzenione składające się z N wierzchołków.

Twoim zadaniem jest obsłużenie Q zapytań postaci:

v k – jaki wierzchołek znajduje się k poziomów nad v.
*/
#include <iostream>
#include <vector>

#define log2(x) ((x) == 0 ? -1 : (31 - __builtin_clz(x)))

using namespace std;

const int MAX_N = 200000;
const int MAX_logN = log2(MAX_N);

void preprocess_sparse_table(vector<vector<int>>& up, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= MAX_logN; j++) {
            if (up[i][j - 1] == -2) break;
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
}

int sparse_table_ancestor(int v, int k, const vector<vector<int>>& up) {
    v--; 
    for (int i = 0; i <= MAX_logN; i++) {
        if (k & (1 << i)) {
            v = up[v][i];
            if (v == -2) return -1;  
        }
    }
    return v + 1; 

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int N, Q;
    cin >> N >> Q;

    vector<vector<int>> up(N, vector<int>(MAX_logN + 1, -2));

    int pom = -2;
    up[0][0] = pom;
    for (int i = 1; i < N; i++){
        cin >> pom;
        up[i][0] = pom - 1;
    }

    preprocess_sparse_table(up, N);

    while (Q--) {
        int v, k;
        cin >> v >> k;
        cout << sparse_table_ancestor(v, k, up) << "\n";
    }

}
