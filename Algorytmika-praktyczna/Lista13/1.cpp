#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N;

        cin >> N;

        int x = 0;

        
        for (int i = 0; i < N; ++i) {
            int a;

            cin >> a;
            x ^= a;
        }

        if (x != 0) cout << "first\n";
        else cout << "second\n";
    }

}
