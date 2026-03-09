/*Zadanie 2 (10 pkt.). Dla ustalonego różnowartościowego ciągu S = (x_0, x_1, ..., x_(n-1)) definiujemy porządek pomiędzy jego niepustymi podciągami A, B w następujący sposób: A < B wtedy i tylko wtedy gdy

A jest prefiksem B, lub
a jest wcześniej niż b w S, gdzie a, b to znaki w A, B na najwcześniejszej pozycji, na której się one różnią.
Przykładowo, dla ciągu S = (a, b, f, c) zachodzi (a, b, c) > (a, b, f, c) oraz (b) < (f) < (f, c).

Napisz program, który dla danego ciągu znaków oblicza jego podciągi z uwzględnieniem powyższej kolejności. Pierwszym, obowiązkowym argumentem wywołania programu jest napis stanowiący ciąg S – możesz założyć, że będzie on dość krótki (do ok. 20 znaków), żeby wykonanie programu nie było zbyt długie. Ewentualne dalsze argumenty określają szczegóły działania programu.

Wywołanie z flagą -a, np. ./a.out abcd -a powinno wypisać wszystkie niepuste podciągi w ww. porządku, czyli w tym przypadku

a
ab
abc
abcd
abd
ac
acd
ad
b
bc
bcd
bd
c
cd
d
Wywołanie z flagą -i [indeks], np. ./a.out adc -i 2 powinno wypisać ten podciąg, który ww. porządku jest na pozycji [indeks] (liczonej od 1), a więc w tym przypadku ad.

Wreszcie wywołanie bez dodatkowej flagi powinno wypisać losową liczbę z odpowiedniego zakresu i, w kolejnym wierszu, podciąg z tej pozycji. Do losowania użyj funkcji rand() z nagłówka stdlib.h (a żeby faktycznie zobaczyć zmienność losowania, najpierw wywołaj srand(time(NULL)), dołączając jeszcze time.h – o szczegóły tego, co tu się dzieje, możesz zapytać osobę prowadzącą pracownię).

Wszystkie niepoprawne wywołania (bez argumentów, z dodatkowym argumentem po -a, bez dodatkowego argumentu po -i, z argumentem po -i nie dającym się zinterpretować jako liczba dodatnia etc.) powinny skutkować wypisaniem odpowiedniego komunikatu o błędzie i wyjściem.

Wskazówka: warto skorzystać z rekurencji i następującej obserwacji: wszystkie podciągi zawierające x_0 będą w porządku wcześniej, niż pozostałe; w dodatku będą one zaczynać się od x_0, po którym będą następować kolejne podciągi (x_1, x_2, ..., x_(n-1)).

(Kiedy S jest uporządkowane alfabetycznie, jak w jednym z powyższych przykładów, to nieprzypadkowo otrzymujemy porządek leksykograficzny. Pusty podciąg wstawiony na początek porządku dalej będzie do niego pasował, ale pomijając go, łatwiej było napisać wskazówkę... Jeśli chcesz, możesz spróbować samemu wymyślić rekurencję, która wygeneruje również pusty podciąg – wtedy, dla spójności, będziemy zakładać, że ma on indeks 0.)

Uwaga: Konieczne może się okazać przekazywanie tablic jako argumentów funkcji. Możesz zapytać o szczegóły osobę prowadzącą pracownię, poczekać do wykładu 14.11 (będzie m.in. o tym wtedy mowa, a następna pracownia, do której należy zrobić to zadanie, jest w odległym terminie 20.11), albo dla uproszczenia użyć zamiast tego tablicy zadeklarowanej globalnie.

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 40000

bool p[MAX_N];
int lp1[MAX_N], lp5[MAX_N], lp7[MAX_N];
int n1 = 0, n5 = 0, n7 = 0;

void liczbypierwsze() {
    for (int i = 0; i < MAX_N; i++) p[i] = true;

    p[0] = p[1] = false;

    for (int i = 2; i * i < MAX_N; i++) {
        if (p[i]) for (int j = i * i; j < MAX_N; j += i) p[j] = false;
    }

    for (int i = 2; i < MAX_N; i++) if (p[i]) lp1[n1++] = i;
}

int ile_czynnikow(int x) {
    int ile = 0;
    for (int i = 0; lp1[i] * lp1[i] < x + 1 && x > 1; i++) {
        while (x % lp1[i] == 0) {
            ile++;
            x /= lp1[i];
        }
    }
    if (x > 1) ile++;
    return ile;
}

void kpierwsze(int k, int* tab, int* ile, int n) {
    for (int i = 2; i < n; i++) {
        if (ile_czynnikow(i) == k) tab[(*ile)++] = i;
    }
}

int* bs(int c, int* t, int len) {
    int l = 0, p = len - 1;
    while (l < p + 1) {
        int mid = (l + p) / 2;
        if (t[mid] == c) return &t[mid];
        if (t[mid] < c) l = mid + 1;
        else p = mid - 1;
    }
    return NULL;
}

int main() {
    int n;
    scanf("%d", &n);

    liczbypierwsze();
    kpierwsze(5, lp5, &n5, n);
    kpierwsze(7, lp7, &n7, n);

    int r = 0;

    for (int i = 0; i < n1 && lp1[i] < n; i++) {
        for (int j = 0; j < n5; j++) {
            int suma_ab = lp1[i] + lp5[j];
            if (suma_ab > n - 1) break;
            int c = n - suma_ab;
            if (bs(c, lp7, n7) != NULL) r++;
        }
    }

    printf("%d\n", r);
    return 0;
}
