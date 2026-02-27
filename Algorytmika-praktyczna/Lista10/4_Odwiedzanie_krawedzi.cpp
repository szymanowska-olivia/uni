/*
Dany jest graf nieskierowany o N wierzchołkach i M krawędziach.

Twoim zadaniem jest znalezienie ścieżki rozpoczynającej i kończącej się w wierzchołku o numerze 1, która przechodzi przez każdą krawędź dokładnie raz.
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<stack<pair<int, int>>> graph;
vector<bool> visited;
vector<int> res;

void DFS(int v){
    while (!graph[v].empty()){
        auto edge = graph[v].top();
        graph[v].pop();
        if (visited[edge.second]) continue;
        visited[edge.second] = true;
        DFS(edge.first);
    }
    res.push_back(v);
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int N, M;
    cin >> N >> M;

    graph.resize(N + 1);
    visited.resize(M, false);
    vector<int> edges(N + 1, 0);
    

    int u, v, idx = 0;
    for (int i = 0; i < M; i++){
        cin >> u >> v;
        graph[u].push({v, idx});
        graph[v].push({u, idx});
        edges[v]++;
        edges[u]++;
        idx++;
        
    }

    for (int i = 1; i < N + 1; i++){
        if (edges[i] % 2 != 0){
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    DFS(1);

    if ( res.size() != M + 1 ) cout << "IMPOSSIBLE";
    else for (int i = 0; i < res.size(); i++) cout << res[i] << " ";
    cout << "\n";
}
