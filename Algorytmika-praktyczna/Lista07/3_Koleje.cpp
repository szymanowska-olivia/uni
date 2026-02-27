/*
Bajtockie Koleje Państwowe postanowiły pójść z duchem czasu i wprowadzić do swojej oferty połączenie InterCity. Ze względu na brak sprawnych lokomotyw, czystych wagonów i prostych torów można było uruchomić tylko jedno takie połączenie. Kolejną przeszkodą okazał się brak informatycznego systemu rezerwacji miejsc. Napisanie głównej części tego systemu jest Twoim zadaniem.

Dla uproszczenia przyjmujemy, że połączenie InterCity przebiega przez N miast ponumerowanych kolejno od 1 do N (miasto na początku trasy ma numer 1, a na końcu N). W pociągu jest M miejsc i między żadnymi dwiema kolejnymi stacjami nie można przewieźć większej liczby pasażerów.

System informatyczny ma przyjmować kolejne zgłoszenia i stwierdzać, czy można je zrealizować. Zgłoszenie jest akceptowane, gdy na danym odcinku trasy w pociągu jest wystarczająca liczba wolnych miejsc, w przeciwnym przypadku zgłoszenie jest odrzucane. Nie jest możliwe częściowe zaakceptowanie zgłoszenia, np. na część trasy, albo dla mniejszej liczby pasażerów. Po zaakceptowaniu zgłoszenia uaktualniany jest stan wolnych miejsc w pociągu. Zgłoszenia przetwarzane są jedno po drugim w kolejności nadchodzenia.

Napisz program, który: wczyta ze standardowego wejścia opis połączenia oraz listę zgłoszonych rezerwacji, obliczy które zgłoszenia zostaną przyjęte, a które odrzucone, zapisze na standardowe wyjście odpowiedzi na wszystkie zgłoszenia.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, Q;
vector<pair<int, int>> tree;

void push(int v, int l, int r) {
    if (tree[v].second != 0) {
        tree[v].first += tree[v].second;
        if (l != r) {
            tree[v * 2].second += tree[v].second;
            tree[v * 2 + 1].second += tree[v].second;
        }
        tree[v].second = 0;
    }
}

int query(int v, int l, int r, int ql, int qr) {
    push(v, l, r);
    if (qr < l || ql > r) return 0;
    if (ql <= l && r <= qr) return tree[v].first;
    int mid = (l + r) / 2;
    return max(query(v * 2, l, mid, ql, qr),query(v * 2 + 1, mid + 1, r, ql, qr));
}

void update(int v, int l, int r, int ul, int ur, int val) {
    push(v, l, r);
    if (ur < l || ul > r) return;
    if (ul <= l && r <= ur) {
        tree[v].second += val;
        push(v, l, r);
        return;
    }
    int mid = (l + r) / 2;
    update(v * 2, l, mid, ul, ur, val);
    update(v * 2 + 1, mid + 1, r, ul, ur, val);
    tree[v].first = max(tree[v * 2].first, tree[v * 2 + 1].first);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    

    cin >> N >> M >> Q;
    int size = 1;

    while (size < N) size <<= 1;

    tree.resize(size * 2, {0, 0});

    for (int i = 0; i < Q; ++i) {
        int P, K, L;
        cin >> P >> K >> L;
        int maxi = query(1, 1, N - 1, P, K - 1);
        if (maxi + L <= M) {
            cout << 'T' << '\n';
            update(1, 1, N - 1, P, K - 1, L);
        } else cout << 'N' << '\n';
    }
}
