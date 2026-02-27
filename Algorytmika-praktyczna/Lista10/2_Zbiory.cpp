/*
Dany jest graf skierowany o N wierzchołkach i M krawędziach.

Przyjmujemy, że dwa wierzchołki u i v powinny zostać przydzielone do jednego zbioru wtedy i tylko wtedy, gdy istnieje ścieżka z u do v oraz z v do u.

Twoim zadaniem jest znaleźć podział na zbiory spełniający powyższe warunki.
*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> graph_rev;
vector<bool> visited;
stack<int> postorder;
vector<int> SCC_nr;

int N, M, ile = 0;

vector<int> comp_min_vertex;

void dfs1(int u) {
    visited[u] = true;
    for (int v : graph[u]) if (!visited[v]) dfs1(v);
    postorder.push(u);
}

void dfs2(int u, int id, int &mini) {
    SCC_nr[u] = id;
    visited[u] = true;
    if (u < mini) mini = u;
    for (int v : graph_rev[u]) {
        if (!visited[v]) dfs2(v, id, mini);
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    graph.resize(N + 1);
    graph_rev.resize(N + 1);
    visited.resize(N + 1, false);
    SCC_nr.resize(N + 1, 0);

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

    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) dfs1(i);
    }

    fill(visited.begin(), visited.end(), false);

    vector<pair<int,int>> comp_info;

    while (!postorder.empty()) {
        int u = postorder.top();
        postorder.pop();
        if (!visited[u]) {
            ile++;
            int mini = N+1;
            dfs2(u, ile, mini);
            comp_info.emplace_back(mini, ile);
        }
    }

    sort(comp_info.begin(), comp_info.end());

    vector<int> new_id(ile + 1);

    for (int i = 0; i < ile; i++) new_id[comp_info[i].second] = i + 1;

    cout << ile << "\n";
    for (int i = 1; i <= N; i++) cout << new_id[SCC_nr[i]] << " ";
    cout << "\n";

}
