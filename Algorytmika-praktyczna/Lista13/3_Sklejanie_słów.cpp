/*
Dane są tekst T o długości N oraz słownik K słów.

Twoim zadaniem jest policzyć na ile sposobów można pociąć tekst na kawałki tak, aby wszystkie pocięte fragmenty były słowami ze słownika.
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_NODES = 1000000;
const int MOD = 1e9+7;

string T;
vector<string> s;
vector<int> dp;
vector<vector<int>> trie(MAX_NODES, vector<int>(26, 0));
vector<bool> leaf(MAX_NODES, false);
int nodes = 1;

void build_Trie(){
    for(string str : s){
        int node = 0;
        for (char c : str) {
            int ch = c - 'a';
            if (trie[node][ch] == 0) trie[node][ch] = nodes++; //brak przejscia
            node = trie[node][ch];
            /*
            for(int i = 0; i < 11; i++){
                for(int j = 0; j < 13; j++){
                    cout << trie[i][j] << " ";
                }
                cout << "\n";
            }
            cout << "nowe\n";
            */
        }
        leaf[node] = true;
    }
    
}

void fill_dp(){
    for (int i = T.size() - 1; i >= 0; i--) { //kolrjny sufiks
        int node = 0;
        for (int j = i; j < T.size(); j++) { //kolejna literka
            int c = T[j] - 'a';
            if (trie[node][c] == 0) break;
            node = trie[node][c];
            if (leaf[node]) dp[i] = (dp[i] + dp[j+1]) % MOD;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int K;
    cin >> T;
    dp.resize(T.size() + 1, 0);
    dp[T.size()] = 1;
    cin >> K;
    s.resize(K);
    for(int i = 0; i < K; i++) cin >> s[i];

    build_Trie();
    fill_dp();
    
    cout << dp[0] << "\n";
}