/*
Dane jest drzewo, składające się z N wierzchołków.

Twoim zadaniem jest obsłużenie Q zapytań postaci:

u v – jaka jest odległość między wierzchołkami u i v.
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int MAX_N = 200001;
vector<int> tree[MAX_N];
vector<int> euler;
vector<int> depth;
int fst[MAX_N];
int d = 0;

void eulerTour(int u, int parent) {
    if (fst[u] == -1) 
        fst[u] = euler.size();

    euler.push_back(u);
    depth.push_back(d);

    for (int v : tree[u]) {
        if (v != parent) {
            d++;
            eulerTour(v, u);
            d--;
            euler.push_back(u);
            depth.push_back(d);
        }
    }
}

void build_st(const vector<int>& depth_, vector<int>& st, int v, int start, int end) {
    if (start == end) {
        st[v] = start;
    } else {
        int mid = (start + end) / 2;
        build_st(depth_, st, 2 * v, start, mid);
        build_st(depth_, st, 2 * v + 1, mid + 1, end);

        int left = st[2 * v];
        int right = st[2 * v + 1];
        st[v] = (depth_[left] < depth_[right]) ? left : right;
    }
}

int find_min(const vector<int>& depth_, const vector<int>& st, int v, int start, int end, int l, int r) {
    if (r < start || end < l)
        return -1;
    if (l <= start && end <= r)
        return st[v];

    int mid = (start + end) / 2;
    int left = find_min(depth_, st, 2 * v, start, mid, l, r);
    int right = find_min(depth_, st, 2 * v + 1, mid + 1, end, l, r);

    if (left == -1) return right;
    if (right == -1) return left;

    return (depth_[left] < depth_[right]) ? left : right;
}

int LCA(int u, int v, const vector<int>& depth_, const vector<int>& st) {
    int left = fst[u];
    int right = fst[v];
    if (left > right) swap(left, right);

    int idx = find_min(depth_, st, 1, 0, depth_.size() - 1, left, right);

    return euler[idx];
}

int main() {
    int N, Q;
    cin >> N >> Q;

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    fill(fst, fst + N + 1, -1);
    eulerTour(1, -1);

    int size = 1;
    while (size < euler.size()) size *= 2;
    vector<int> st(2 * size, -1);
    build_st(depth, st, 1, 0, euler.size() - 1);

    for (int i = 0; i < Q; ++i) {
        int u, v;
        cin >> u >> v;
        int lca = LCA(u, v, depth, st);
        cout << depth[fst[u]] + depth[fst[v]] - 2 * depth[fst[lca]] << '\n';
    }
}
