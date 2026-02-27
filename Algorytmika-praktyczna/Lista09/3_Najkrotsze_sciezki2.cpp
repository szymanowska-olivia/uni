/*
Dany jest ważony i nieskierowany graf o N wierzchołkach i M krawędziach oraz Q zapytań postaci:

dla danych wierzchołków u oraz v znajdź długość najkrótszej ścieżki pomiędzy tymi wierzchołkami.
*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void Warshall (vector<vector <long long>>& DST, int n){
    long long suma;
    for (int v = 1; v < n + 1; v++){
        for (int u = 1; u < n + 1; u++){
            for (int w = 1; w < n + 1; w++){
                if (DST[u][v] == LLONG_MAX || DST[v][w] == LLONG_MAX) suma = LLONG_MAX;
                else suma = DST[u][v] + DST[v][w];
                DST[u][w] = min(DST[u][w], suma);
                DST[w][u] = DST[u][w];
            } 
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int N, M, Q;
    cin >> N >> M >> Q;
    vector<vector <long long>> DST(N+1, vector<long long>(N+1, LLONG_MAX));   
    int u, v;
    long long w;
    for(int i = 0; i < M; i++){
        cin >> u >> v >> w;
        DST[u][v] = min(DST[u][v], w);
        DST[v][u] = DST[u][v];
    }
    for(int i = 0; i < N + 1; i++) DST[i][i] = 0;
    int qu, qv;

    Warshall(DST, N);

    for (int i = 0 ; i < Q; i++){
        cin >> qu >> qv;
        if (DST[qu][qv] == LLONG_MAX) cout << "-1" << "\n"; 
        else cout << DST[qu][qv] << "\n";         
    } 
        
}