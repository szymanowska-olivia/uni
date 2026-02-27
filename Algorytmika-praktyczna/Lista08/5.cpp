/*
Dane jest drzewo ukorzenione, składające się z N wierzchołków. Każdy z wierzchołków ma przypisaną do siebie wartość.

Twoim zadaniem jest obsłużenie Q zapytań postaci:

1 v x – zamień wartość w wierzchołku v na x,
2 v – podaj sumę wartości wierzchołków z poddrzewa v.
*/
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 200001;
vector<int> tree[MAX_N];
vector<long long> euler_values;
int in[MAX_N], out[MAX_N], value[MAX_N];
int timer = 0;

void eulerTour(int u, int parent) {
    in[u] = euler_values.size();
    euler_values.push_back(value[u]);

    for (int v : tree[u]) {
        if (v != parent) eulerTour(v, u);
    }

    out[u] = euler_values.size();
    euler_values.push_back(0); 
}

vector<long long> st;
int st_size = 1;

void build_st() {
    while (st_size < euler_values.size()) {
        st_size *= 2;
    }

    st.assign(2 * st_size, 0);

    for (int i = 0; i < euler_values.size(); ++i) {
        st[st_size + i] = euler_values[i];
    }

    for (int i = st_size - 1; i >= 1; --i) {
        st[i] = st[2 * i] + st[2 * i + 1];
    }
}

long long summ(int v, int tl, int tr, int l, int r) {
    if (l > r) {
        return 0;
    }
    if (l == tl && r == tr) {
        return st[v];
    }
    int tm = (tl + tr) / 2;
    return summ(v * 2, tl, tm, l, min(r, tm)) + summ(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

void update(int idx, long long newVal) {
    idx += st_size;
    st[idx] = newVal;

    while (idx > 1) {
        idx /= 2;
        st[idx] = st[2 * idx] + st[2 * idx + 1];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N, Q;
    cin >> N >> Q;

    for (int i = 1; i <= N; ++i) cin >> value[i];

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    eulerTour(1, -1);

    build_st();

    for (int i = 0; i < Q; ++i) {
        int query, v;
        cin >> query >> v;

        if (query == 1) {
            long long x;
            cin >> x;
            value[v] = x;
            update(in[v], x);  
        } else if (query == 2) {
            cout << summ(1, 0, st_size - 1, in[v], out[v] - 1) << '\n';
        }
    }

    return 0;
}
