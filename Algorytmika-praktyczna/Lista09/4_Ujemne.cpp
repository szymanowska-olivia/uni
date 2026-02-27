/*
Dany jest ważony i skierowany graf o N wierzchołkach i M krawędziach.

Twoim zadaniem jest znalezienie w podanym grafie cyklu o ujemnej sumie wag.
*/
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm> // dla reverse

using namespace std;

void Bellman (vector<long long>& DST, vector<vector<pair<long long, int>>>& q, int n, bool& ujemny, int& pocz_cykl, vector<int>& p){
    int i = 0;
    while(1){
        i++;
        bool update = false;
        for(int j = 0; j < q.size(); j++){
            for(int k = 0; k < q[j].size(); k++){
                long long waga = q[j][k].first;
                int v1 = j, v2 = q[j][k].second;

                if (DST[v2] == LLONG_MAX) continue;

                if (DST[v1] > DST[v2] + waga) {
                    DST[v1] = DST[v2] + waga;
                    p[v1] = v2; //sciezka do cyklu
                    update = true;

                    if (i == n){  
                        ujemny = true;
                        pocz_cykl = v1; //gdzie zaczal sie cykl
                        return;
                    }
                }
            }
        }
        if (!update) break;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int N, M;
    cin >> N >> M;
    vector<long long> DST(N+1, LLONG_MAX);
    vector<vector<pair<long long, int>>> q(N+1);
    int u, v;
    long long w;
    for(int i = 0; i < M; i++){
        cin >> u >> v >> w;
        q[u].emplace_back(w, v);
    }

    bool ujemny = false;
    int pocz_cykl = -1;
    vector<int> p(N+1, -1);

        fill(DST.begin(), DST.end(), LLONG_MAX);
        for (int i = 1; i <= N; i++) DST[i] = 0;
        ujemny = false;
        pocz_cykl = -1;

        Bellman(DST, q, N, ujemny, pocz_cykl, p);
       
    if (ujemny){
            
        cout << "YES\n";
            
        int x = pocz_cykl;
        for (int j = 0; j < N + 1; j++) x = p[x]; //cofka do pierwszego wierszcholka w cyklu

            
        vector<int> cykl;
            
        int y = x;
            
        while (1) {
            cykl.push_back(y);
            y = p[y];
            if (y == x) break;
        }
            
        cykl.push_back(x);         
        for (int k = 0; k < cykl.size(); k++) cout << cykl[k] << " ";
        cout << "\n";
        
    }
    else cout << "NO\n";
}
