/*
Dane jest ukorzenione drzewo o N wierzchołkach. Wierzchołki te numerujemy liczbami naturalnymi od 1 do N, gdzie 1 jest korzeniem. Dodatkowo, każdy wierzchołek ma przypisany pewien kolor.

Definiujemy zbiór wierzchołka jako zbiór kolorów, które występują w jego poddrzewie.
Twoim zadaniem jest określenie dla każdego wierzchołka liczby różnych kolorów w jego zbiorze.
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

const int MAX_N = 200005;

vector<int> t[MAX_N];
int color[MAX_N];
int ile[MAX_N];
unordered_set<int>* colors_stree[MAX_N];

void dfs(int node, int parent) {
    colors_stree[node] = new unordered_set<int>();
    colors_stree[node]->insert(color[node]);

    int child_count = t[node].size();
    for (int idx = 0; idx < child_count; idx++) {
        int child = t[node][idx];
        if (child == parent) continue;

        dfs(child, node);

        if (colors_stree[child]->size() > colors_stree[node]->size()) swap(colors_stree[child], colors_stree[node]);

        unordered_set<int>::iterator it;
        for (it = colors_stree[child]->begin(); it != colors_stree[child]->end(); ++it) colors_stree[node]->insert(*it);

        delete colors_stree[child];
    }

    ile[node] = colors_stree[node]->size();
}

int main() {
    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) cin >> color[i];

    for (int i = 1; i <= N - 1; i++) {
        int a, b;
        cin >> a >> b;
        t[a].push_back(b);
        t[b].push_back(a);
    }

    dfs(1, -1);

    for (int i = 1; i <= N; i++) cout << ile[i] << " ";
    cout << "\n";

}
