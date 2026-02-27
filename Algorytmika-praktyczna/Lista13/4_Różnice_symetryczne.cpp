/*
Dany jest ciąg liczb a1, …, aN oraz liczba K.

Twoim zadaniem jest policzyć ile jest takich par indeksów (i,j), że 1 ≤ i < j ≤ N oraz ai ⊕ aj ≥ K, gdzie ⊕ oznacza operację xor.
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_NODES = 1000000;
const int MAX_BIT = 31;

int K;
vector<int> s;
vector<vector<int>> trie(MAX_NODES, vector<int>(2, 0));
vector<int> cnt(MAX_NODES, 0);
int nodes = 1;

void build_Trie(){
    for(int l : s){
        int node = 0;
        for (int i = MAX_BIT; i > -1; --i) {
            int bit = (l >> i) & 1;

                if (trie[node][bit] == 0) trie[node][bit] = nodes++; //brak przejscia
                node = trie[node][bit];
                /*
                for(int i = 0; i < 11; i++){
                    for(int j = 0; j < 13; j++){
                        cout << trie[i][j] << " ";
                    }
                    cout << "\n";
                }
                cout << "nowe\n";
                */

            cnt[node]++;
        }
    }
    
}

long long cnt_lesser(int num, int node, int bit) {

    if ((node == 0 || bit < 0)&& bit != MAX_BIT) return 0; 
    int a_bit = (num >> bit) & 1;
    int k_bit = (K >> bit) & 1;

    long long ile = 0;
    if (k_bit == 1) {

        if (trie[node][a_bit] != 0) ile += cnt[trie[node][a_bit]]; // wszystkie z gałęzi a_bit
        ile += cnt_lesser(num, trie[node][1 ^ a_bit], bit - 1); // szukanie dalej w przeciwnej gałęzi
    } else ile += cnt_lesser(num, trie[node][a_bit], bit - 1); // kbit == 0 schodzenie tylko w ta sama galaz =abit (XOR 0)

    return ile;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    cin >> K;
    s.resize(N);
    for(int i = 0; i < N; i++) cin >> s[i];

    build_Trie();

    long long less = 0;
    for (int i = 0; i < N; i++) less += cnt_lesser(s[i], 0, MAX_BIT) - 1; // para z samym sobą

    less /= 2; // (i,j) i (j,i)

    long long total = (long long)N * (N - 1) / 2;
    
    cout << total - less << "\n";
}