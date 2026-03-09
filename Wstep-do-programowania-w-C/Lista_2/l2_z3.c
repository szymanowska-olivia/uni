/*Kaktusy
Meksykański biolog hoduje kaktusy na n grządkach po m kaktusów w każdej. Pierwszego dnia pożywka podawana jest kaktusom na pierwszej grządce, drugiego – na pierwszej i drugiej, k-tego – na grządkach od 1 do k, n-tego – na wszystkich grządkach, n + 1-szego – znowu tylko na pierwszej, i tak dalej. Pod wpływem pożywki każdy kaktus (jeśli rośnie na odpowiedniej grządce) zmienia swoją wysokość z h na:

3 h + 1, jeśli h jest nieparzyste;
h / 2, jeśli h jest parzyste.
Na standardowym wejściu w pierwszym wierszu podane są kolejno nieujemne n ≤ 150, m ≤ 200 oraz d ≤ 1000000 – czas trwania eksperymentu w dniach. W kolejnych n wierszach podanych jest po m nieujemnych liczb – wysokości kolejnych kaktusów na danej grządce, które nie przekraczają 38000000. Jeśli któraś wysokość jest podana jako 0, oznacza to, że na danym stanowisku nie ma żadnego kaktusa, więc taka wysokość ani się nie zmienia, ani nie wpływa na łączną wysokość wszystkich kaktusów.

Napisz program, który wczyta takie wejście i wypisze na standardowe wyjście jedną liczbę – największą osiągniętą w czasie trwania eksperymentu łączną wysokość kaktusów (uwzględniając zarówno stan sprzed pierwszego dnia podawania pożywki, jak i po d-tym dniu).

Przykłady
A
Wejście:

1 1 13
27
Wyjście:

322
Kaktus o wysokości 27 po czternastym dniu urósłby do wysokości 484 (a później jeszcze bardziej), ale tu eksperyment trwa tylko 13 dni.

B
Wejście:

2 2 1000
5 21
85 341
Wyjście:

1320
Takie kaktusy raz urosną, a potem będą się tylko kurczyć, ale pierwszego dnia rosną tylko niskie kaktusy z pierwszej grządki. Drugiego dnia rosną kaktusy z drugiej grządki (te z pierwszej już się kurczą) i to wtedy osiągane jest maksimum (8+32 na pierwszej grządce, 256+1024 na drugiej).

C
Wejście:

3 3 0
80 756 764
93 44 198
179 0 113
Wyjście:

2227
d = 0, więc należy zwrócić sumę wysokości początkowych.

Uwagi i wskazówki
Zasady zmiany wysokości kaktusów nieprzypadkowo są takie, jak w hipotezie Collatza. Podane ograniczenie wysokości pojedynczego kaktusa (38 milionów) dotyczy jej wartości początkowej.

Najlepiej używać wywołań scanf podobnych do scanf("%d", &zmienna); (tj. zawierających w napisie formatującym tylko specyfikator(y) formatu, bez żadnych dodatków, w tym spacji) – wtedy można nie przejmować się tym, że na wejściu między liczbami czasami są spacje, a czasami znaki złamania wiersza; kolejne wywołania scanf po prostu wczytają kolejne liczby z wejścia, bez rozróżnienia, jakim dokładnie białym znakiem są rozdzielone.*/
#include <stdio.h>

int main() {
    long long p[150][200], h;
    int n, m, d;
    int g;
    long long suma = 0, maxsuma = 0;

    scanf("%d%d%d", &n, &m, &d);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%lld", &p[i][j]);
            suma += p[i][j];
        }
    }

    maxsuma = suma;
    suma = 0;

    for (int i = 0; i < d; i++) {
        g = i % n + 1;
        suma = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (j < g) {
                    h = p[j][k];
                    if (h != 0) {
                        if (h % 2 == 0) h /= 2;
                        else h = 3 * h + 1;
                        p[j][k] = h;
                    }
                }
                suma += p[j][k];
            }
        }

        if (suma > maxsuma) maxsuma = suma;
        suma = 0;
    }

    printf("%lld", maxsuma);

    return 0;
}
