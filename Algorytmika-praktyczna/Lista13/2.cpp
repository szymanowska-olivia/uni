#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t[7] = {0, 1, 0, 1, 2, 3, 2};

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        int xor_sum = 0;
        for (int i = 0; i < N; ++i) {
            int a;
            cin >> a;
            xor_sum ^= t[a % 7];
        }

        if (xor_sum != 0) cout << "first\n";
        else cout << "second\n";
    }

}
