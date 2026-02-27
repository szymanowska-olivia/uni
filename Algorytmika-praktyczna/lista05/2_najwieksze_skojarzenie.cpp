/*
Dane jest drzewo składające się z N wierzchołków.

Skojarzeniem w drzewie nazwiemy taki podzbiór krawędzi tego drzewa, że żadne dwie z nich nie mają wspólnego końca.

Twoim zadaniem jest znalezienie rozmiaru największego skojarzenia w podanym drzewie.
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 200000;

pair<int, int> dfs(int v, const vector<vector<int>>& tree, vector<bool>& visited) {
    visited[v] = true;
    int match_w_root = 0, match_without = 0, zysk = 0;
    
    for (long unsigned int i = 0; i < tree[v].size(); i++) {
        int child = tree[v][i];
        if (!visited[child]) {
            pair<int, int> res = dfs(child, tree, visited);
            
            match_without += max(res.first, res.second);
            zysk = max(zysk, res.second - res.first + 1);
        }
    }
    match_w_root = match_without + zysk;
    
    return {match_w_root, match_without};
}

int max_matching(vector<vector<int>>& tree, int N) {
    vector<bool> visited(N + 1, false);
    pair<int, int> res = dfs(1, tree, visited);
    int SK = res.first, SK_ = res.second;
    return max(SK, SK_);
}

int main() {
    int N, a, b;
    cin >> N;

    vector<vector<int>> tree(N + 1);

    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    cout << max_matching(tree, N) << endl;
}
