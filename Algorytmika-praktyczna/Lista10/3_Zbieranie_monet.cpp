/*
Dany jest graf skierowany o N wierzchołkach i M krawędziach. Każdy wierzchołek ma przypisana pewną liczbę monet.

Twoim zadaniem jest policzyć jaką maksymalnie liczbę monet da się zebrać chodząc po grafie wzdłuż wyznaczonych krawędzi, zakładając, że można rozpocząć i skończyć w wybranym przez siebie wierzchołku. Każdy zbiór monet można zebrać tylko jednokrotnie.
*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> graph_rev;
vector<bool> visited;
stack<int> postorder;
vector<int> SCC_nr;

int N, M, ile = 0;

vector<long long> coins; 
vector<long long> coins_summed; 
vector<vector<int>> graph_scc;
vector<int> incoming_edges;
vector<long long> dp;

void dfs1(int u) {
    visited[u] = true;
    for (int v : graph[u]) if (!visited[v]) dfs1(v);
    postorder.push(u);
}

void dfs2(int u, int id, long long &sum) {
    SCC_nr[u] = id;
    visited[u] = true;
    sum += coins[u];
    for (int v : graph_rev[u]) {
        if (!visited[v]) dfs2(v, id, sum);
    }
}

void topo_sort(vector<vector<int>>& graph, vector<int>& incoming_edges, vector<int>& res){
    queue<int> pq;
    
    for (int i = 1; i < incoming_edges.size(); i++) if (incoming_edges[i] == 0) pq.push(i);

    while (!pq.empty()) {
        int curr = pq.front(); 
        res.push_back(curr);
        pq.pop();

        for (int next : graph[curr]) {
            incoming_edges[next]--;

            if (incoming_edges[next] == 0) pq.push(next);
        }

    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0); 

    cin >> N >> M;
    coins.resize(N + 1);
    graph.resize(N + 1);
    graph_rev.resize(N + 1);
    visited.resize(N + 1, false);
    SCC_nr.resize(N + 1, 0);

    for (int i = 1; i <= N; i++) cin >> coins[i];

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph_rev[v].push_back(u);
    }

    for (int i = 1; i <= N; ++i) {
        sort(graph[i].begin(), graph[i].end());
        sort(graph_rev[i].begin(), graph_rev[i].end());
    }

    for (int i = 1; i <= N; ++i) if (!visited[i]) dfs1(i);

    fill(visited.begin(), visited.end(), false);

    while (!postorder.empty()) {
        int u = postorder.top();
        postorder.pop();
        if (!visited[u]) {
            ile++;
            long long sum = 0;
            dfs2(u, ile, sum);
            coins_summed.push_back(sum); 
        }
    }

    graph_scc.resize(ile + 1);
    incoming_edges.resize(ile + 1, 0);
    for (int u = 1; u <= N; u++) {
        for (int v : graph[u]) {
            int cu = SCC_nr[u];
            int cv = SCC_nr[v];
            if (cu != cv) {
                graph_scc[cu].push_back(cv);
                incoming_edges[cv]++;
            }
        }
    }

    vector<int> res;
    topo_sort(graph_scc, incoming_edges, res);

    dp.resize(ile + 1, 0);
    for (int i = 1; i <= ile; i++) dp[i] = coins_summed[i - 1]; 

    for (int u : res) {
        for (int v : graph_scc[u]) {
            if (dp[v] < dp[u] + coins_summed[v - 1]) dp[v] = dp[u] + coins_summed[v - 1];
        }
    }

    long long result = 0;
    for (int i = 1; i <= ile; i++) result = max(result, dp[i]);

    cout << result << "\n";
}
