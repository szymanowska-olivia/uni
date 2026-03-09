/*Zadanie 1 (10 pkt. na pracowni, później 5 pkt.). To zadanie ma dwie niezależne części, należy zatem przesłać/przedstawić dwa programy.

A. Napisz program, który wczytuje ze standardowego wejścia dodatnie liczby k oraz n (n ≤ 30), a następnie n liczb naturalnych oznaczających wagi kolejnych elementów w pewnym n-elementowym zbiorze. Chcemy wyliczyć, ile podzbiorów zadanego zbioru elementów ma sumaryczną wagę nie większą niż k. Do wygenerowania wszystkich podzbiorów można użyć odpowiedniej rekurencji, ale w tym zadaniu użyjemy innego podejścia.

Liczby od 0 do 2^n-1 możemy traktować jako reprezentacje wszystkich podzbiorów, gdzie podzbiór zawiera element numer i wtedy i tylko wtedy, gdy bit i jest zapalony (równy 1). Np. 45 = 101001 oznacza podzbiór (indeksów) {0, 3, 5}, gdzie liczymy bity od najmniej znaczącego (i od zera). Należy więc iterować przez odpowiedni zakres liczb, gdzie każda liczba reprezentuje dokładnie jeden podzbiór, i każdorazowo wyliczać sumę wag elementów zawartych w podzbiorze, a jeśli nie zostanie przekroczone k, to zwiększać wynikowy licznik.

Przykładowo, dla wejścia

2 3
1 1 1

odpowiedź to 7 – możemy wybrać dowolny podzbiór poza całym zbiorem. Natomiast dla wejścia

45 5
30 20 1 10 50s

poprawna odpowiedź to 12: zawsze możemy wziąć lub nie wziąć elementu o wadze 1 oraz (niezależnie) 10, a spośród elementów o wagach 20 i 30 możemy wybrać najwyżej jeden (trzy możliwości), zatem 2x2x3=12.*/
#include <stdio.h>

int main() {
    int k, n, ile = 0, w[30];

    scanf("%d%d", &k, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    for (int i = 0; i < (1 << n); i++) {
        int suma = 0;
        for (int j = 0; j < n; j++) if (i & (1 << j))  suma += w[j];

        if (suma <= k) ile++;
    }

    printf("%d\n", ile);

    return 0;
}
