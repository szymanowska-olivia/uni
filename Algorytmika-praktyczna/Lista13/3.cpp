#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        int xor_sum = 0, x;
        for (int i = 0; i < N; ++i) {
            cin >> x;
            xor_sum ^= x;
        }

        cout << (xor_sum ? "first" : "second") << '\n';
    }

    return 0;
}
