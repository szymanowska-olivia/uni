/*
Dany jest ciąg zawierający N liczb całkowitych. Twoim zadaniem jest usuwać elementy z listy na podanych pozycjach i wypisywać usunięte elementy.
*/
#include <iostream>
#include <vector>

using namespace std;

void remove(vector<int>& list, vector<int>& st, int p, int size) {
    int v = 1, curr = p;
    while (v < size) {
        int l = 2 * v, r = 2 * v + 1;
        if (st[l] >= curr)
            v = l;
        else {
            curr -= st[l];
            v = r;
        }
    }
    int index = v - size;
    cout << list[index] << " ";
    st[v] = 0;
    for (v /= 2; v >= 1; v /= 2)
        st[v] = st[2 * v] + st[2 * v + 1];
}

int main() {
    int n;
    cin >> n;
    vector<int> list(n);
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> list[i];
    for (int i = 0; i < n; i++)cin >> p[i];
    int size = 1;
    while (size < n) size <<= 1;
    vector<int> st(2 * size, 0);
    for (int i = 0; i < size; i++) st[size + i] = (i < n ? 1 : 0);
    for (int i = size - 1; i >= 1; i--) st[i] = st[2 * i] + st[2 * i + 1];
    for (int i = 0; i < n; i++) remove(list, st, p[i], size);
    cout << "\n";
}
