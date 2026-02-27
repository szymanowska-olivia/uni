/*
Dany jest graf skierowany o N wierzchołkach i M krawędziach. Wypisz jego wierzchołki w takiej kolejności, że jeśli w grafie istnieje krawędź (u,v), to wierzchołek u jest przed wierzchołkiem v.
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void topo_sort(vector<vector<int>>& graph, vector<int>& incoming_edges, vector<int>& res){
    priority_queue<int, vector<int>, greater<int>> pq;

    for(int i = 1; i < incoming_edges.size(); i++) if (incoming_edges[i] == 0) pq.push(i);
    
    while (!pq.empty()){
        int curr = pq.top();
        res.push_back(curr);
        pq.pop();

        for (int i = 0; i < graph[curr].size(); i++){
            int next = graph[curr][i];
            incoming_edges[next]--;

            if (incoming_edges[next] == 0) pq.push(next);
        }

    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N + 1);
    vector<int> incoming_edges(N + 1, 0);
    vector<int> res;

    int u, v;
    for (int i = 0; i < M; i++){
        cin >> u >> v;
        graph[u].push_back(v);
        incoming_edges[v]++;
    }

    topo_sort(graph, incoming_edges, res);

    if (res.size() < N) cout << "IMPOSSIBLE";
    else for (int i = 0; i < res.size(); i++) cout << res[i] << " ";
    cout << "\n";
}
