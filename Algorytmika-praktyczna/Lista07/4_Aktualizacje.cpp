/*
Dany jest ciąg liczb całkowitych a1, …, aN.

Twoim zadaniem jest obsłużyć Q zapytań następujących typów:

zwiększ wartości elementów na pozycjach z przedziału [x,y] o v,
ustaw wartości elementów na pozycjach z przedziału [x,y] na v,
policz sumę elementów na pozycjach z przedziału [x,y].
*/
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1 << 19;

int N, Q;
vector<long long> a;
vector<long long> sum(4 * MAXN);
vector<long long> lazy_add(4 * MAXN, 0);
vector<long long> lazy_set(4 * MAXN, -1); 

void push(int v, int tl, int tr) {
    if (lazy_set[v] != -1) {
        sum[v] = lazy_set[v] * (tr - tl + 1);
        if (tl != tr) {
            lazy_set[2 * v] = lazy_set[v];
            lazy_add[2 * v] = 0;
            lazy_set[2 * v + 1] = lazy_set[v];
            lazy_add[2 * v + 1] = 0;
        }
        lazy_set[v] = -1;
    }
    if (lazy_add[v] != 0) {
        sum[v] += lazy_add[v] * (tr - tl + 1);
        if (tl != tr) {
            if (lazy_set[2 * v] != -1)
                lazy_set[2 * v] += lazy_add[v];
            else
                lazy_add[2 * v] += lazy_add[v];

            if (lazy_set[2 * v + 1] != -1)
                lazy_set[2 * v + 1] += lazy_add[v];
            else
                lazy_add[2 * v + 1] += lazy_add[v];
        }
        lazy_add[v] = 0;
    }
}

void build(int v, int tl, int tr) {
    if (tl == tr) {
        sum[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        sum[v] = sum[2 * v] + sum[2 * v + 1];
    }
}

void update_add(int v, int tl, int tr, int l, int r, long long val) {
    push(v, tl, tr);
    if (r < tl || tr < l)
        return;
    if (l <= tl && tr <= r) {
        lazy_add[v] += val;
        push(v, tl, tr);
    } else {
        int tm = (tl + tr) / 2;
        update_add(2 * v, tl, tm, l, r, val);
        update_add(2 * v + 1, tm + 1, tr, l, r, val);
        sum[v] = sum[2 * v] + sum[2 * v + 1];
    }
}

void update_set(int v, int tl, int tr, int l, int r, long long val) {
    push(v, tl, tr);
    if (r < tl || tr < l)
        return;
    if (l <= tl && tr <= r) {
        lazy_set[v] = val;
        lazy_add[v] = 0;
        push(v, tl, tr);
    } else {
        int tm = (tl + tr) / 2;
        update_set(2 * v, tl, tm, l, r, val);
        update_set(2 * v + 1, tm + 1, tr, l, r, val);
        sum[v] = sum[2 * v] + sum[2 * v + 1];
    }
}

long long query_sum(int v, int tl, int tr, int l, int r) {
    push(v, tl, tr);
    if (r < tl || tr < l)
        return 0;
    if (l <= tl && tr <= r)
        return sum[v];
    int tm = (tl + tr) / 2;
    return query_sum(2 * v, tl, tm, l, r) + query_sum(2 * v + 1, tm + 1, tr, l, r);
}

int main() {
ios_base::sync_with_stdio(false);
cin.tie(0);
cout.tie(0);


    cin >> N >> Q;
    a.resize(N);
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    build(1, 0, N - 1);

    while (Q--) {
        int q;
        cin >> q;
        if (q == 1) {
            int l, r;
            long long v;
            cin >> l >> r >> v;
            update_add(1, 0, N - 1, l - 1, r - 1, v);
        } else if (q == 2) {
            int l, r;
            long long v;
            cin >> l >> r >> v;
            update_set(1, 0, N - 1, l - 1, r - 1, v);
        } else if (q == 3) {
            int l, r;
            cin >> l >> r;
            cout << query_sum(1, 0, N - 1, l - 1, r - 1) << "\n";
        }
    }

    return 0;
}
