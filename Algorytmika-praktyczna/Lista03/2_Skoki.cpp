/*
Dany jest ciąg liczb całkowitych x1, x2, …, xN oraz Q zapytań składających się z dwóch liczb całkowitych a oraz b.

Twoim zadaniem jest dla każdego zapytania policzyć sumę xa + xa + b + xa + 2 ⋅ b, xa + 3 ⋅ b, …, aż do końca ciągu.
*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void sum_preprocess(int N, int n, vector<int> &x, vector<vector<long long>> &s){
    for (int b = 1; b <= n; b++) {
        for (int a = N - 1; a >= 0; a--) {
            if (a + b < N) s[b][a] = x[a] + s[b][a + b];  
            else s[b][a] = x[a];  
        }
    }
}

int main() {
    int N;
    cin >> N;
    
    vector<int> x(N);
    for (int i = 0; i < N; i++) cin >> x[i];
    
    int Q;
    cin >> Q;

    int n = sqrt(N);

    vector<vector<long long>> s(n + 1, vector<long long>(N, -1));
    
    sum_preprocess(N, n, x, s);

    for (int q = 0; q < Q; q++) {
        int a, b;
        cin >> a >> b;
        a--; 
        
        if (b <= n)  cout << s[b][a] <<"\n";
        else {
            long long sum = 0;
            for (int i = a; i < N; i += b) sum += x[i];
            cout << sum <<"\n";
        }
    }

    return 0;
}
