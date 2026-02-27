/*
W pewnym magicznym kurzym gnieździe nadeszła wiosna, a razem z nią… sezon genealogii!

Mama Kura, znana jako wierzchołek numer 1, postanowiła wreszcie uporządkować swoje drzewo rodzinne. Każde z jej N potomków (dzieci, dzieci ich dzieci… i tak dalej) zna tylko swojego rodzica. Teraz, gdy cała rodzina zjechała się na Wielkanocne Śniadanie, pojawił się dylemat: które kurczę jest najstarszym wspólnym przodkiem dwóch wybranych kuzynów?

Twoim zadaniem jest pomóc kurzej rodzinie znaleźć odpowiedzi na Q zapytań, każde z nich dotyczy dwóch kurczaków u i v, a Twoją rolą jest wskazanie ich najwyższego wspólnego przodka.
*/
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int N, Q;
    cin >> N >> Q;

    for (int i = 1; i < N; i++) {
        int parent;
        cin >> parent;
//        parent--;
//      tree[parent].push_back(i); 
//        tree[i].push_back(parent);
    }

    while (Q--) {
        int v, u;
        cin >> v >> u;
        cout << 1 << "\n";
    }
}
