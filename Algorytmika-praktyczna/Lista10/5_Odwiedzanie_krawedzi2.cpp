/*
Dany jest graf skierowany o N wierzchołkach i M krawędziach.

Twoim zadaniem jest znalezienie ścieżki rozpoczynającej się w wierzchołku o numerze 1 i kończącej się w wierzchołku N, która przechodzi przez każdą krawędź dokładnie raz.
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<stack<int>> graph;
vector<int> res;

void DFS(int v, int N){
    while (!graph[v].empty()){
        auto edge = graph[v].top();
        graph[v].pop();
        DFS(edge, N);
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
    vector<int> incoming_edges(N + 1, 0);
    vector<int> outgoing_edges(N + 1, 0);

    

    int u, v, idx = 0;
    for (int i = 0; i < M; i++){
        cin >> u >> v;
        graph[u].push(v);
        incoming_edges[v]++;
        outgoing_edges[u]++;
        idx++;
        
    }

    if (incoming_edges[1] + 1 != outgoing_edges[1] || incoming_edges[N] != outgoing_edges[N] + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 2; i < N; i++){
        if (incoming_edges[i] != outgoing_edges[i]){
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    DFS(1, N);

    if ( res.size() != M + 1 ) cout << "IMPOSSIBLE";
    else for (int i = res.size() - 1; i > -1 ; i--) cout << res[i] << " ";
    cout << "\n";
}
