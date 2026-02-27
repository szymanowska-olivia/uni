/*
Dane są dwa ciągi, z których każdy ma N różnych elementów. Dane jest również Q zapytań, a każde z nich składa się z dwóch par liczb całkowitych l1, r1, l2 i r2.

Twoim zadaniem jest odpowiedzieć na każde zapytanie: czy elementy na pozycjach od l1 do r1 (włącznie) w pierwszym ciągu tworzą permutację elementów z przedziału od l2 do r2 (również włącznie) w drugim ciągu?
*/
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<long long> H1, H2;
vector<long long> D(1000001);
int N, Q;

const long long MOD = 1000000007LL;

void preprocessing (){
   for (int i = 0; i <= 1000000; i++)  D[i] = (rand() * 1LL << 32) ^ rand();
    int curr1, curr2;

    H1[0] = D[H1[0]] % MOD;
    H2[0] = D[H2[0]] % MOD;

    for (int i = 1; i < N; i++) {

        H1[i] = (D[H1[i]] + H1[i - 1]) % MOD;
        H2[i] = (D[H2[i]] + H2[i - 1]) % MOD;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    srand(time(0));

    cin >> N >> Q;

    H1.resize(N);
    H2.resize(N);

    for(int i = 0; i < N; i++) cin >> H1[i];
    for(int i = 0; i < N; i++) cin >> H2[i];

    preprocessing();

    while(Q--){
        int l1,r1,l2,r2;

        cin >> l1 >> r1 >> l2 >> r2;

        long long sum1 = H1[r1 - 1] - (l1 > 1 ? H1[l1 - 2] : 0);
        long long sum2 = H2[r2 - 1] - (l2 > 1 ? H2[l2 - 2] : 0);

        sum1 = (sum1 + MOD) % MOD;
        sum2 = (sum2 + MOD) % MOD;

        //i += S.size() - 1;
        if (sum1 == sum2) cout << "TAK" << "\n";
        else cout << "NIE" << "\n";

    }

}
