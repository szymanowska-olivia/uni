/*
Dany jest ważony i skierowany graf o N wierzchołkach i M krawędziach. Wagi na krawędziach mogą być ujemne.

Twoim zadaniem jest policzenie największej sumy wag krawędzi na ścieżce z wierzchołka 1 do N. Ścieżka ta może przechodzić przez wierzchołki i krawędzie wielokrotnie.
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void Bellman(vector<long long>& DST, vector<vector<pair<long long,int>>>& q, int n, bool& dodatni_cykl, vector<bool>& visited) {
    DST[1] = 0;
    for (int i = 1; i < n; i++) {
        bool updated = false;
        for (int u = 1; u <= n; u++) {
            if (DST[u] == LLONG_MIN) continue;
            for (auto& edge : q[u]) {
                int v = edge.second;
                long long waga = edge.first;
                if (DST[u] + waga > DST[v]) {
                    DST[v] = DST[u] + waga;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }

    for (int u = 1; u <= n; u++) {
        if (DST[u] == LLONG_MIN) continue;
        for (auto& edge : q[u]) {
            int v = edge.second;
            long long waga = edge.first;
            if (DST[u] + waga > DST[v]) {
                dodatni_cykl = true;

                vector<int> s = {v};
                while (!s.empty()) {
                    int x = s.back(); s.pop_back();
                    if (visited[x]) continue;
                    visited[x] = true;
                    for (auto& k : q[x]) {
                        if (!visited[k.second]) s.push_back(k.second);
                    }
                }
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
    vector<vector<pair<long long,int>>> q(N+1);

    for (int i = 0; i < M; i++) {
        int u,v; long long w;
        cin >> u >> v >> w;
        q[u].emplace_back(w, v);
    }

    vector<long long> DST(N+1, LLONG_MIN);
    bool dodatni_cykl = false;
    vector<bool> visited(N+1, false);

    Bellman(DST, q, N, dodatni_cykl, visited);

    if (dodatni_cykl && visited[N]) cout << -1 << "\n";
    else cout << DST[N] << "\n";

    return 0;
}
