/*
Na osi OX zostały rozłożone w pewnych odległościach punkty o numerach 1, 2, …, N. Następnie dane jest M zdań postaci ,,parzystość odcinka od a do b jest równa p’’. Twoim zadaniem jest znaleźć największe takie w, że pierwsze w spośród podanych zdań może być prawdziwe.
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000005;

int parent[MAXN], parity[MAXN];

int find(int x) {
    if (parent[x] == x) return x;

    int og_parent = parent[x];
    parent[x] = find(parent[x]);
    parity[x] ^= parity[og_parent];

    return parent[x];
}

bool polacz(int a, int b, int p) {
    int fa = find(a), fb = find(b);

    if (fa == fb) return ((parity[a] ^ parity[b]) == p);

    parent[fa] = fb;
    parity[fa] = parity[a] ^ parity[b] ^ p;


    return true;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> a(M), b(M), p(M); 

    for (int i = 0; i < M; i++) {
        cin >> a[i] >> b[i] >> p[i];
        a[i]--;  b[i]--;
    }

    for (int i = 0; i <= N; i++) {
        parent[i] = i;
        parity[i] = 0;
    }

    int w = 0;
    for (int i = 0; i < M; i++) {
        if (!polacz(a[i], b[i], p[i])) break;
        w = i + 1;
    }

    cout << w << "\n";
}
