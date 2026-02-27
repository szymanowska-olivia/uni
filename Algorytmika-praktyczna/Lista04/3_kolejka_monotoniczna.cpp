/*
Dany jest ciąg N liczb całkowitych oraz Q zapytań składających się z dwóch liczb a i b.

Twoim zadaniem jest odpowiedzieć dla każdego zapytania jakie jest minimum na przedziale [a,b].
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> v(N);

    for (int i = 0; i < N; i++) cin >> v[i];

    vector<tuple<int, int, int>> queries(Q);
    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        queries[i] = {b, a, i};
    }

    sort(queries.begin(), queries.end()); 

    vector<pair<int, int>> dq; 
    vector<int> result(Q);


    int j = 0;

    for (auto [b, a, idx] : queries) {
        while (j <= b) {
            while (!dq.empty() && dq.back().first >= v[j]) dq.pop_back();
            dq.emplace_back(v[j], j);
            j++;
        }

        auto it = lower_bound(dq.begin(), dq.end(), a, [](const pair<int, int>& elem, int val) { return elem.second < val;});
        result[idx] = it->first;
    }

    for (int x : result) cout << x << '\n';

}
