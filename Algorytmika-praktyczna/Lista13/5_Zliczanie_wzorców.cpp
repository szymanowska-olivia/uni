#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int ALPHABET_SIZE = 26;
const int MAX_NODES = 1000000;

vector<vector<int>> trie(MAX_NODES, vector<int>(ALPHABET_SIZE, 0));
vector<int> dp(MAX_NODES, 0);
vector<bool> leaf(MAX_NODES, false);
vector<vector<int>> output(MAX_NODES); 
int nodes = 1;

int K; 
vector<string> patterns;

void build_Trie() {
    for (int i = 0; i < K; i++) {
        const string &p = patterns[i];
        int node = 0;
        for (char c : p) {
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
        output[node].push_back(i); 
    }
}

void build_failure() {
    queue<int> q;
    for (int ch = 0; ch < ALPHABET_SIZE; ch++) {
        int next = trie[0][ch];
        if (next != 0) {
            dp[next] = 0;
            q.push(next);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int ch = 0; ch < ALPHABET_SIZE; ch++) {
            int next = trie[node][ch];
            if (next == 0) continue;

            int f = dp[node];
            while (f > 0 && trie[f][ch] == 0) f = dp[f];
            if (trie[f][ch] != 0) f = trie[f][ch];
            dp[next] = f;

            //cout << "dp" << next << f << endl;

            for (int idx : output[f]) output[next].push_back(idx);
            if (!output[f].empty()) leaf[next] = true;

            q.push(next);
        }
    }
}

vector<int> aho_corasick_search(const string &T) {
    vector<int> occ(K, 0);
    int node = 0;
    for (char c : T) {
        int ch = c - 'a';
        while (node > 0 && trie[node][ch] == 0) node = dp[node];
        if (trie[node][ch] != 0) node = trie[node][ch];

        for (int pattern_idx : output[node]) occ[pattern_idx]++;
    }
    return occ;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string T;
    cin >> T;

    cin >> K;
    patterns.resize(K);
    for (int i = 0; i < K; i++) cin >> patterns[i];

    build_Trie();
    build_failure();

    vector<int> result = aho_corasick_search(T);

    for (int cnt : result) cout << cnt << "\n";

}
