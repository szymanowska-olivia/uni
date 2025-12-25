//Olivia Szymanowska 353133
//Lista 1 zadanie 1
#include <stdio.h>

long long factorials_imp(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) result *= i;
    return result;
}

long long factorials_rec(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    return n * factorials_rec(n - 1);
}

long long binom(int n, int k) {
    return factorials_imp(n) / (factorials_imp(k) * factorials_imp(n - k));
}

void Pascal(int n){
    for (int i = 0; i < n + 1; i++) printf("%lld ", binom(n, i));
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    Pascal(n);

    return 0;
}