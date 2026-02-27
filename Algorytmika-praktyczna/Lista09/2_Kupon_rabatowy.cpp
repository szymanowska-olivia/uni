/*
Dany jest ważony i skierowany graf o N wierzchołkach i M krawędziach. Każda krawędź ma przypisany koszt, który trzeba zapłacić, żeby przez nią przejść.

Twoim zadaniem jest znalezienie najtańszej ścieżki z wierzchołka 1 do wierzchołka N. Jednakże, na jednej z krawędzi możesz użyć kuponu rabatowego, który sprawia, że zamiast kosztu w zapłacisz za przejście po niej ⌊w/2⌋.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>

using namespace std;

void dijkstra (vector<long long>& nodes, vector<long long>& nodeswith, const vector<vector<pair<long long, int>>>& q){
    priority_queue<tuple<long long, int, int>,vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> que;
    que.push({0, 1, 0});
    while (!que.empty()) {
        int mini = get<1>(que.top());
        long long waga = get<0>(que.top());
        int world = get<2>(que.top());

        que.pop();
        long long zapisany;
        
        if (world == 0)  zapisany = nodes[mini];
        else zapisany = nodeswith[mini];


        if (waga > zapisany) continue;

        for (auto& sasiedni : q[mini]) {
            int next = sasiedni.second;
            long long weight = sasiedni.first;


            if (nodes[mini] + weight < nodes[next]) {
                nodes[next] = nodes[mini] + weight;
                que.emplace(nodes[next], next, 0);

            }
            if (nodes[mini] + (weight/2) < nodeswith[next]){
                    nodeswith[next] = nodes[mini] + (weight/2);
                    que.emplace(nodeswith[next], next, 1);
            }            
            else if (nodeswith[mini] + weight < nodeswith[next]) {
                nodeswith[next] = nodeswith[mini] + weight;
                que.emplace(nodeswith[next], next, 1);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int N, M;
    cin >> N >> M;
    vector<long long> nodes(N+1, LLONG_MAX);
    vector<long long> nodeswith(N+1, LLONG_MAX);
    vector<vector<pair<long long, int>>> q(N+1);
    int u, v;
    long long w;
    for(int i = 0; i < M; i++){
        cin >> u >> v >> w;
        q[u].emplace_back(w, v);
    }
    nodes[1] = 0;
    nodeswith[1] = 0;

    dijkstra(nodes, nodeswith, q);

    cout << nodeswith[N] <<"\n";
}
