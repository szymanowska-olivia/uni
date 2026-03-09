/*Zadanie 2 (10 pkt.). Rozważamy dwie tablice S i T tego samego rozmiaru, zawierające liczby naturalne z zakresu [1, 1000], bez powtórzeń w obrębie jednej tablicy. Chcemy (szybko) odpowiadać na zapytania, czy podtablice S[i...i+k] i T[j...j+k] zawierają dokładnie te same liczby (niekoniecznie w tej samej kolejności). Jednym z rozwiązań jest haszowanie, tzn. przypisywanie podzbiorom (pseudo)losowych liczb je reprezentujących w ten sposób, że dwa różne podzbiory z bardzo niskim prawdopodobieństwem otrzymają taką samą liczbę-reprezentanta. (Haszowanie to bardzo szeroka koncepcja o licznych realizacjach i zastosowaniach, tutaj jest to tylko jeden z wielu przykładów.)

Najpierw wypełniamy pomocniczą tablicę r[1001] losowymi liczbami (p. wyjaśnienia w zadaniu z listy 4). Haszem liczby i będzie r[i], natomiast haszem zbioru wielu liczb będzie XOR (bitowa alternatywa wykluczająca) ich haszy. Potrzebujemy również tablic prefiksowych, które zawierają XORy haszy wszystkich prefiksów każdej tablicy, tzn. tablicy prefiksowej P dla S takiej, że

P[0] = r[S[0]],
P[1] = r[S[0]] ^ r[S[1]],
P[2] = r[S[0]] ^ r[S[1]] ^ r[S[2]] itd.,
jak również Q zdefiniowanej analogicznie dla T. Przygotowawszy takie struktury, możemy w czasie stałym uzyskać hasz dowolnej podtablicy S[i...i+k], którym (z własności operacji XOR – jest przemienna i odwrotna do samej siebie, tj. x ^ y ^ y = x) będzie P[i+k] ^ P[i-1] (zastanów się, co należy zrobić, gdy i = 0). Wreszcie (również z przemienności XOR) stwierdzamy, że S[i...i+k] zawiera dokładnie ten sam zbiór liczb co T[j...j+k] wtedy i tylko wtedy, gdy ich hasze są takie same.

Program powinien wczytać długość tablic S i T i kolejno te dwie tablice, następnie liczbę zapytań z, a później z zapytań o równość zbiorów na przedziałach, gdzie pojedyncze zapytanie składa się z trzech liczb i, j, k. Przykładowo, dla:

8
1 2 3 4 5 6 7 8
7 5 6 8 4 3 2 1
5
0 1 0
7 3 0
0 0 7
0 4 2
0 4 3

kolejne odpowiedzi to

NIE – 1 ≠ 5,
TAK – 8 = 8,
TAK – całe tablice mają tę samą zawartość, tylko w innej kolejności,
NIE – {1, 2, 3} ≠ {4, 3, 2},
TAK – w obu tablicach na zadanych pozycjach znajduje się zbiór {1, 2, 3, 4}.*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_W 1001
#define MAX 100000

void losowe_hashe(unsigned int* r) {
    srand((unsigned int)time(NULL));
    for (int i = 1; i < MAX_W; i++) r[i] = (unsigned int)rand();
}

void tablice_prefixow(unsigned int* t, unsigned int* p, unsigned int* r, int n) {
    p[0] = r[t[0]];
    for (int i = 1; i < n; i++) p[i] = p[i - 1] ^ r[t[i]];
}

unsigned int hash_podtablicy(unsigned int* p, int pocz, int kon) {
    if (pocz == 0) return p[kon];
    return p[kon] ^ p[pocz - 1];
}

int main() {
    int n;
    scanf("%d", &n);

    unsigned int S[MAX], T[MAX], r[MAX_W], P[MAX], Q[MAX];
    bool rowne[MAX];
    for (int i = 0; i < n; i++) scanf("%u", &S[i]);
    for (int i = 0; i < n; i++) scanf("%u", &T[i]);

    losowe_hashe(r);
    tablice_prefixow(S, P, r, n);
    tablice_prefixow(T, Q, r, n);

    int z;
    scanf("%d", &z);

    for (int q = 0; q < z; q++) {
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);

        unsigned int hash_S = hash_podtablicy(P, i, i + k);
        unsigned int hash_T = hash_podtablicy(Q, j, j + k);

        rowne[q] = (hash_S == hash_T);
    }

    for (int q = 0; q < z; q++) {
        if (rowne[q]) printf("TAK\n");
        else printf("NIE\n");
    }

    return 0;
}
