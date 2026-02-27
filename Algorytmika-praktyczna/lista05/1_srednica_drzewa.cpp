/*
Dane jest drzewo składające się z N wierzchołków.

Średnicą drzewa nazwiemy największą odległość między dwoma wierzchołkami w tym drzewie.

Twoim zadaniem jest znalezienie średnicy podanego drzewa.
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 200000;

pair<int, int> dfs(int v, const vector<vector<int>>& tree, vector<bool>& visited) {
    visited[v] = true;
    int maxW = -1, maxW2 = -1, maxSr = 0;

    for (long unsigned int i = 0; i < tree[v].size(); i++) {
        int child = tree[v][i];
        if (!visited[child]) {
            pair<int, int> res = dfs(child, tree, visited);
            int w = res.second;

            if (w > maxW) {
                maxW2 = maxW;
                maxW = w;
            } else if (w > maxW2) maxW2 = w;

            maxSr = max(maxSr, res.first);
        }

    }

    maxSr = max(maxSr, maxW + maxW2 + 2);

    return {maxSr, maxW + 1}; 
}

int srednica(vector<vector<int>>& tree, int N) {
    vector<bool> visited(N + 1, false);
    
    pair<int, int> res = dfs(1, tree, visited);
    return res.first;
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

    cout << srednica(tree, N) << endl;
}
