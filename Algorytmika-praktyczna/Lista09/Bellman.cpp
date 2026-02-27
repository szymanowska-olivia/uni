#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void Bellman (vector<long long>& DST, vector<vector<pair<long long, int>>>& q, int n){
    for(int i = 1; i < n; i++){
        bool update = false;
        for(int j = 1; j < q.size(); j++){
            for(int k = 0; k < q[j].size(); k++){   //przechodzimy po wszystkich krawedziach i aktualizujemy wagi w 2 strony
                long long waga = q[j][k].first;                   
                int v1 = j, v2 = q[j][k].second;
                bool krawedz1 = true, krawedz2 = true; 

                if (DST[v2] == LLONG_MAX && DST[v1] == LLONG_MAX) continue;
                //cout << v1 << " " << v2 << " w: " << waga << "\n";
                if (DST[v2] != LLONG_MAX){ DST[v1] = min(DST[v1], DST[v2] + waga); update = true; }
                else krawedz1 = false;

                if (DST[v1] != LLONG_MAX){ DST[v2] = min(DST[v2], DST[v1] + waga); update = true; } 
                else krawedz2 = false;

                if (!krawedz1 && krawedz2){ DST[v1] = min(DST[v1], DST[v2] + waga); update = true; }
                if (!krawedz2 && krawedz1){ DST[v2] = min(DST[v2], DST[v1] + waga); update = true; }

                //cout << DST[v1] << " " << DST[v2] << "\n";

                /*
                tutaj chodzi o to ze moze byc jakis wierzcholek do ktorego jeszcze nie doszlismy
                i wtedy jezeli chcemy ustawic drugi na jego podstawie to wybuchnie bo long int przekroczyl long int
                zatem jezeli jeden z nich tak ma to czekamy az sie zaktualizuhje na podstawie drugiego i wtedy dopiero ustawiamy drugi
                jezeli oba sa posrane to nic nie robimy to potem ogarniemy ze nie ma tej krawedzi czy cos tam :3
                */
            }
        }
        if (!update) break;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int N, M, Q;
    cin >> N >> M >> Q;
    vector<long long> DST(N+1, LLONG_MAX);
    vector<vector <long long>> res(N+1, vector<long long>(N+1, LLONG_MAX));   
    vector<vector<pair<long long, int>>> q(N+1);
    int u, v;
    long long w;
    for(int i = 0; i < M; i++){
        cin >> u >> v >> w;
        q[u].emplace_back(w, v);
    }
    int qu, qv;

    for (int i = 0 ; i < Q; i++){
        cin >> qu >> qv;

        if (res[qu][qv] == LLONG_MAX){
            fill(DST.begin(), DST.end(), LLONG_MAX);
            DST[qu] = 0;

            Bellman(DST, q, N);
            for(int j = 1; j <= N; j++){
                if (DST[j] == LLONG_MAX){
                    res[j][qu] = -1;
                    res[qu][j] = -1;
                } 
                else {
                    res[j][qu] = DST[j];   
                    res[qu][j] = DST[j];                   
                }
             }
         }
        
        cout << res[qu][qv] << "\n";          
    } 
        
}