/*
Dane jest drzewo ukorzenione, składające się z N wierzchołków.

Twoim zadaniem jest obsłużenie Q zapytań postaci:

u v – jaki jest najniższy wspólny przodek wierzchołków u i v.
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
            if (up[i][j - 1] == -1) break;
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
}

void dfs(int v, int parent, int& cnt, vector<pair<int, int>>& count, const vector<vector<int>>& tree, vector<int>& depth) {
    count[v].first = cnt++;
    depth[v] = (v == parent ? 0 : depth[parent] + 1);

    for (int child : tree[v]) {
        if (child != parent) 
            dfs(child, v, cnt, count, tree, depth);
    }

    count[v].second = cnt++;
}

bool is_ancestor(int a, int b, const vector<pair<int, int>>& count) {
    return count[a].first <= count[b].first && count[a].second >= count[b].second;
}

int sparse_table_ancestor(int v, int u, const vector<vector<int>>& up, const vector<pair<int, int>>& count, const vector<int>& depth, int N) {
    if (is_ancestor(v, u, count)) return v;
    if (is_ancestor(u, v, count)) return u;

    int x = v;
    for (int i = log2(N); i >= 0; i--) {
        if (up[x][i] != -1 && !is_ancestor(up[x][i], u, count)) {
            x = up[x][i];
        }
    }

    return up[x][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int N, Q;
    cin >> N >> Q;

    vector<vector<int>> up(N, vector<int>(MAX_logN + 1, -1));
    vector<pair<int, int>> count(N);
    vector<vector<int>> tree(N);
    vector<int> depth(N);

    for (int i = 1; i < N; i++){
        int parent;
        cin >> parent;
        parent--;
        up[i][0] = parent;
        tree[parent].push_back(i); 
        tree[i].push_back(parent);
    }

    preprocess_sparse_table(up, N);
    int cnt = 1;
    dfs(0, 0, cnt, count, tree, depth);

    while (Q--) {
        int v, u;
        cin >> v >> u;
        v--; u--;
        cout << (sparse_table_ancestor(v, u, up, count, depth, N) + 1) << "\n";
    }
}
