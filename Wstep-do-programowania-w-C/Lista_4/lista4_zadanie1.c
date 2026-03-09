/*Zadanie 1 (10 pkt. na pracowni, później 5 pkt.). Napisz program, który rekurencyjnie oblicza n-ty wyraz ciągu zadanego dla n ≥ k równością f(n) = a_0 * f(n-1) + a_1 * f(n-2) + ... a_(k-1) * f(n-k). Program powienien przyjmować 2k+1 argumentów:

pierwszy argument to liczba k > 0;
kolejne k argumentów to liczby a_0, a_1, ..., a_(k-1);
ostatnie k argumentów to liczby f(0), f(1), ..., f(k-1).
Poza pierwszym, argumenty mogą być niecałkowite (przy typowej konfiguracji powłoki pewnie będzie należało użyć kropki jako separatora części ułamkowej), do ich zinterpretowania możesz użyć atof z stdlib.h. Nieujemną liczbę n program powinien wczytywać ze standardowego wejścia.

Zadbaj, aby twój program sprawdzał poprawność podanych argumentów.*/
#include <stdio.h>
#include <stdlib.h>


double fn(int n, int k, double a[], double f[]) {
    if (n < k) {
        return f[n];
    }

    double suma = 0.0;
    for (int i = 0; i < k; i++) {
        suma += a[i] * fn(n - i - 1, k, a, f);
    }
    return suma;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("BLAD");
        return 1;
    }

    int k = atoi(argv[1]);
    if (k <= 0) {
        printf("BLAD");
        return 1;
    }

    if (argc != 2 * k + 2) {
        printf("BLAD");
        return 1;
    }

    double a[k], f[k];

    for (int i = 0; i < k; i++)  a[i] = atof(argv[2 + i]);
    for (int i = 0; i < k; i++) f[i] = atof(argv[2 + k + i]);

    int n;
    scanf("%d", &n);
    if (n < 0) {
        printf("BLAD");
        return 1;
    }


    double wynik = fn(n, k, a, f);

    printf("f(%d) = %f\n", n, wynik);

    return 0;
}
