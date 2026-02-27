/*
Dany jest ważony i skierowany graf o N wierzchołkach i M krawędziach.

Twoim zadaniem jest policzenie odległości z wierzchołka 1 do wszystkich pozostałych wierzchołków.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

void dijkstra (vector<long long>& nodes, const vector<vector<pair<long long, int>>>& q){
    priority_queue<pair<long long, int>,vector<pair<long long, int>>, greater<pair<long long, int>>> que;
    que.push({0, 1});
    while (!que.empty()) {
        int mini = que.top().second;
        long long waga = que.top().first;
        que.pop();

        if (waga > nodes[mini]) continue;

        for (auto& sasiedni : q[mini]) {
            int next = sasiedni.second;
            long long weight = sasiedni.first;

            if (nodes[mini] + weight < nodes[next]) {
                nodes[next] = nodes[mini] + weight;
                que.emplace(nodes[next], next);
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
    vector<vector<pair<long long, int>>> q(N+1);
    int u, v;
    long long w;
    for(int i = 0; i < M; i++){
        cin >> u >> v >> w;
        q[u].emplace_back(w, v);
    }
    int cnt = N;
    int mini = 1;
    nodes[1] = 0;

    dijkstra(nodes, q);

    for(int i = 1; i < N + 1; i++) cout << nodes[i] << " ";
    cout<<"\n";
}
