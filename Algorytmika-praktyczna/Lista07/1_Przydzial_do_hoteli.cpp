/*
Na ulicy znajduje się N hoteli. Dla każdego hotelu znana jest liczba wolnych pokoi. Twoim zadaniem jest przydzielanie pokoi hotelowych grupom turystów. Wszyscy członkowie jednej grupy chcą zatrzymać się w tym samym hotelu.

Grupy będą przychodziły do Ciebie jedna po drugiej, i dla każdej z nich znana jest liczba potrzebnych pokoi. Zawsze przydzielasz grupę do pierwszego hotelu, który ma wystarczającą liczbę wolnych pokoi. Po przydzieleniu, liczba wolnych pokoi w hotelu się zmniejsza.
*/
#include <iostream>
#include <vector>
using namespace std;

int find_hotel(int x, vector<int>& st, int v, int l, int r, int size) {
    if (st[v] < x) return -1;
    if (l == r) {
        st[v] -= x;
        return l;
    }

    int mid = (l + r) / 2;
    int res;

    if (st[2 * v] >= x) res = find_hotel(x, st, 2 * v, l, mid, size);
    else res = find_hotel(x, st, 2 * v + 1, mid + 1, r, size);

    st[v] = max(st[2 * v], st[2 * v + 1]);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


    int n, q;
    cin >> n >> q;

    int size = 1;
    while (size < n) size *= 2;
    vector<int> st(2 * size);
    for (int i = 0; i < n; i++) cin >> st[size + i];
    for (int i = size - 1; i >= 1; i--) st[i] = max(st[2 * i], st[2 * i + 1]);


    for (int i = 0; i < q; i++) {
        int needed;
        cin >> needed;
        int res = find_hotel(needed, st, 1, 0, size - 1, size);
        if (res == -1) cout << "0 ";
        else cout << res + 1 << " ";
    }

    cout << "\n";
}
