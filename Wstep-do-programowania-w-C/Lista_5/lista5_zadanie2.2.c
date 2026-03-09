/*Zadanie 2 (10 pkt.). Napisz dwa programy – pierwszy z nich będzie generował wartości funkcji, a drugi drukował "wykres" funkcji o wartościach przeczytanych ze standardowego wejścia.

Program generujący ma wypisać na standardowe wyjście liczbę całkowitą n, a potem n liczb (niekoniecznie całkowitych, ale dla funkcji całkowitoliczbowej nie ma sensu wypisywać części ułamkowych) będących wartościami funkcji w kolejnych argumentach (możesz przyjąć, że są to argumenty od 0 do n-1). n ma być podawane jako argument wywołania, a jeśli go nie będzie, to domyślnie ma wynosić 80.

Funkcję wybierz sam(a) – może być dowolna, byle choć trochę ciekawa (liniowa o wybranych na stałe parametrach ciekawa nie jest). Jeśli zbiór jej wartości dla domyślnego zbioru argumentów to Z, to różnica pomiędzy maksimum i minimum zbioru Z ∪ {0} powinna być pomiędzy 10 a 40.

Jeśli chcesz, możesz coś tu dodatkowo skomplikować, np. użyć losowości (p. wyjaśnienia w zadaniu z poprzedniej listy) lub wczytywać dodatkowe parametry z parametrów wywołania czy (mniej ciekawie) standardowego wejścia.

Program drukujący ma przeczytać ze standardowego wejścia liczbę całkowitą n, a potem n liczb (w ogólności zmiennoprzecinkowych) i wydrukować wykres słupkowy o wartościach odpowiadających kolejnym liczbom (oczywiście po zaokrągleniu). Na wykresie ma być widoczna oś X zaznaczona znakami '=', a słupki (nad lub pod osią, w zależności od znaku wartości) należy zaznaczyć znakami '#' (trzeba też będzie oczywiście drukować odpowiednią liczbę spacji). Liczbę drukowanych wierszy dostosuj do ekstremów zbioru Z ∪ {0}.

Jako argumenty wywołania program powinien akceptować:

-b skutkujące wydrukowaniem dodatkowo obramowania wykresu, składającego się ze znaków '|' (segmenty pionowe obramowania), '-' (segmenty poziome obramowania), oraz '+' (narożniki obramowania, a także jego "przecięcia" z osią X); jeśli oś będzie na brzegu wykresu (tj. wartości po zaokrągleniu będą wszystkie nieujemne bądź niedodatnie) to należy potraktować ją jako część obramowania i nie drukować dodatkowego wiersza;
-m NAPIS skutkujący użyciem kolejnych znaków z NAPIS zamiast wyżej wymienionych jako elementu słupka, osi X, i ew. pionowego, poziomego, i narożnego obramowania; NAPIS powinien mieć długość 2, a jeśli podano -b, to 5.
Argumenty są opcjonalne i mogą występować w dowolnej kolejności, a ich niepoprawna postać (np. brak NAPIS po -m lub jego zła długość, kilkukrotne powtórzenie -m, rzeczy inne niż opisane) powinna skutkować natychmiastowym wyjściem z programu.

Drukowanie wykresu możesz zaprogramować bez użycia dodatkowej pamięci na jego przygotowanie, ale jeśli wolisz jej użyć, to zadbaj o to, by samo drukowanie było tak proste jak instrukcja for (int i = 0, i < m, i++) puts(wykres[i]); gdzie (jak widać) wykres to tablica napisów. Dałoby się zresztą zrobić to tak, by wystarczył pojedynczy puts (i to bez rezygnowania z wygody, jaką daje dwuwymiarowa tablica), ale to może trochę przesada.

Program generujący funkcję nie powinien wypisywać nic, czego nie umie przetworzyć program drukujący wykres, tj. powinno się je dać wywołać dosłownie przekierowując potok wyjściowy pierwszego na wejściowy drugiego, bez żadnej "ręcznej" interwencji. Pliki źródłowe powinny nazywać się odpowiednio gen.c oraz graph.c.*/
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

void wykres(int g, int d, int* t, int n, bool b, char* znaki) {
    if (b && g > 0) {
        printf("%c%c", znaki[4], znaki[3]);
        for (int j = 0; j < n; j++) printf("%c%c", znaki[3], znaki[3]);
        printf("%c\n", znaki[4]);
    }


    for (int i = g; i > 0; i--) {
        if (b) printf("%c", znaki[2]);
        printf(" ");
        for (int j = 0; j < n; j++) {
            if (t[j] > i - 1) printf("%c ", znaki[0]);
            else printf("  ");
        }
        if (b) printf("%c", znaki[2]);
        printf("\n");
    }

    if (b) printf("%c", znaki[4]);
    printf("%c", znaki[1]);
    for (int j = 0; j < n; j++) printf("%c%c", znaki[1], znaki[1]);
    if (b) printf("%c", znaki[4]);

    printf("\n");
    for (int i = -1; i > d - 1; i--) {
        if (b) printf("%c", znaki[2]);
        printf(" ");
        for (int j = 0; j < n; j++) {
            if (t[j] < i + 1) printf("%c ", znaki[0]);
            else printf("  ");
        }
        if (b) printf("%c", znaki[2]);
        printf("\n");
    }


    if (d < 0 && b) {
        printf("%c%c", znaki[4], znaki[3]);
        for (int j = 0; j < n; j++) printf("%c%c", znaki[3], znaki[3]);
        printf("%c", znaki[4]);
        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    int n, t[1000], maxi = INT_MIN, mini = INT_MAX;
    bool b = false, m = false;
    char cus[2] = "ab", custom[5] = "#=|-+";

    if (argc > 1 && !strcmp(argv[1], "-b")) {
        b = true;
        //printf("%d\n",b);
        if (argc > 2) {
            if (!strcmp(argv[2], "-m") && argc == 4 && strlen(argv[3]) == 5) {
                m = true;
                strcpy(custom, argv[3]);
            }
            else {
                printf("BLAD\n");
                return 1;
            }
        }
    }
    else if (argc > 1 && argv[1] == "-m") {
        if (argc == 3 && strlen(argv[2]) == 2) {
            m = true;
            strcpy(cus, argv[2]);
        }
        else {
            printf("BLAD\n");
            return 1;
        }
    }


    scanf("%d", &n);
    //printf("Hello World");

    for (int i = 0; i < n; i++) {
        double a;
        scanf("%lf", &a);
        t[i] = (int)round(a);
        if (t[i] < mini) mini = t[i];
        if (t[i] > maxi) maxi = t[i];
    }

    printf("\n");
    int g = maxi, d = mini;
    //printf("%d\n",g);

    if (m && !b) {
        if (g <= 0 && d <= 0) wykres(0, d, t, n, b, cus);
        else if (g > 0 && d < 0) wykres(g, d, t, n, b, cus);
        else if (g >= 0 && d >= 0) wykres(g, 0, t, n, b, cus);
    }
    else {
        if (g <= 0 && d <= 0) wykres(0, d, t, n, b, custom);
        else if (g > 0 && d < 0) wykres(g, d, t, n, b, custom);
        else if (g >= 0 && d >= 0) wykres(g, 0, t, n, b, custom);
    }





    return 0;
}