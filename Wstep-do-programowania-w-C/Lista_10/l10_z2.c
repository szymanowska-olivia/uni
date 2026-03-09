/*Nader Szczególne Liczby
Najwyższy numerolog Mezopotamii próbuje ustalić zestaw szczęśliwych liczb na przyszły rok. Oczywiście, nie mogą one zależeć od czynników tak kapryśnych jak układ gwiazd czy przelot ptaków; szczęśliwych liczb musi być nie za dużo, nie za mało, a w sam raz. Dlatego WOW (Wydział Obliczeń Wróżbiarskich) codziennie musi testować różne koncepcje nadwornego numerologa. Dzisiejszego ranka zadanie jest prostsze niż zwykle. Należy wczytać liczby x, y i policzyć, ile jest liczb w przedziale [x,y] takich, że jednocześnie:
-suma pierwszych czterech cyfr jest podzielna przez 22,
-suma cyfr na pozycjach parzystych jest większa od sumy cyfr na pozycjach nieparzystych o przynajmniej 19,
-liczba zawiera trzy sąsiednie cyfry '3' i dwie sąsiednie cyfry '7'.

Pierwsze cyfry to te najbardziej znaczące, do tego najbardziej znacząca cyfra jest na pozycji nieparzystej. Liczba 17784333 spełnia ostatni warunek.

Pewnym kłopotem jest to, że możnowładcy babilońscy dawno znudzili się małymi liczbami, dlatego numerolog musi operować na dużych wartościach!

Wejście
W pierwszym i jedynym wierszu wejścia znajdują się naturalne liczby 0 < x,y < 10^13 (tj. 10000000000000).

Wyjście
Na standardowe wyjście należy podać odpowiedź na zapytanie Arcynumerologa.

Przykłady
Przykład A
Wejście
1 1000000

Wyjście
0

Żadna z tak małych liczb nie spełnia wymogów.

Przykład B
Wejście
1 1777073339

Wyjście
1

Tylko liczba 1777073339 spełnia wymogi. Suma pierwszych czterech cyfr to 1+7+7+7=22. Suma cyfr na pozycjach parzystych to 7+7+7+3+9=33, nieparzystych 1+7+3+3=14. Liczba zawiera trzy sąsiednie cyfry '7', ale tym lepiej.

Przykład C
Wejście
1800000000 2000000000

Wyjście
6

Szukane liczby to 1939333778, 1939333779, 1939333877, 1939333977, 1939773338 oraz 1939773339.

Uwagi
Jak można wywnioskować na podstawie limitów na wielkość liczb na wejściu, pętla sprawdzająca kolejno wszystkie liczby w przedziale nie może zadziałać zbyt dobrze. Polecamy rozważyć generowanie liczb rekurencyjnie, cyfra po cyfrze, jak w programach rekurencji z nawrotami. Można wtedy przerywać procedurę w odpowiednich momentach, gdy nie ma już szans na uzyskanie na końcu poprawnej liczby. Przykładowo, gdy pierwsze cztery cyfry nie spełniają warunku, nie ma sensu generować pozostałych cyfr. Potrzebne mogą być jeszcze nieco bardziej złożone dodatkowe warunki, np. gdy wygenerowaliśmy już większość cyfr i jest pewne, że nie uda nam się 'zmieścić' na pozostałych miejscach trzech sąsiednich trójek, lub uzyskać odpowiednio wysokiej sumy cyfr na indeksach parzystych, itd.

Proszę także pamiętać, że SKOS przerywa testowanie programu przy pierwszym przekroczeniu limitu czasu, zatem 'niepełny' raport testowania oznaczać może zbyt wolne działanie na ostatnim wyświetlanym teście.*/#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CYFRY 13

bool szczesliwe(char *str, int dl) {
    int suma4 = 0;
    for (int i = 0; i < 4 && i < dl; i++) {
        suma4 += str[i] - '0';
    }
    if (suma4 % 22 != 0) {
        printf("Nie spełnia warunku suma4 %% 22 == 0: %s\n", str);
        return false;
    }

    int p_suma = 0, np_suma = 0;
    for (int i = 0; i < dl; i++) {
        if (i % 2 == 0) {
            np_suma += str[i] - '0';
        } else {
            p_suma += str[i] - '0';
        }
    }
    if (p_suma <= np_suma + 19) {
        printf("Nie spełnia warunku p_suma > np_suma + 19: %s\n", str);
        return false;
    }

    int ile3 = 0, ile7 = 0;
    bool dobre3 = false, dobre7 = false;
    for (int i = 0; i < dl; i++) {
        if (str[i] == '3') {
            ile3++;
            if (ile3 == 3) {
                dobre3 = true;
            }
        } else {
            ile3 = 0;
        }
        if (str[i] == '7') {
            ile7++;
            if (ile7 == 2) {
                dobre7 = true;
            }
        } else {
            ile7 = 0;
        }
    }
    if (!dobre3 || !dobre7) {
        printf("Nie spełnia warunku trzy '3' i dwa '7': %s\n", str);
        return false;
    }

    return true;
}

void generuj_liczby(char *cur, int p, int dl, int suma4, int np_suma, int p_suma, int ile3, int ile7, int *ile, long long x, long long y) {
    printf("generuj_liczby: p=%d, dl=%d, suma4=%d, np_suma=%d, p_suma=%d, ile3=%d, ile7=%d\n", p, dl, suma4, np_suma, p_suma, ile3, ile7); // Debugowanie
    if (p == dl) {
        cur[p] = '\0';
        long long liczba = atoll(cur);
        printf("Sprawdzanie liczby: %s\n", cur); // Debugowanie
        if (liczba >= x && liczba <= y && szczesliwe(cur, dl)) {
            (*ile)++;
            printf("Znaleziono liczbe: %s\n", cur); // Debugowanie
        }
        return;
    }

    if (p >= 4 && suma4 % 22 != 0) {
        printf("Przerwanie generowania: suma4 %% 22 != 0\n"); // Debugowanie
        return;
    }
    if (p > 0 && p_suma <= np_suma + 19 && dl - p > 1) {
        printf("Przerwanie generowania: p_suma <= np_suma + 19\n"); // Debugowanie
        return;
    }
    if (dl - p < 3 - ile3 || dl - p < 2 - ile7) {
        printf("Przerwanie generowania: za mało miejsca na 3 '3' lub 2 '7'\n"); // Debugowanie
        return;
    }

    for (char cyfra = (p == 0 ? '1' : '0'); cyfra <= '9'; cyfra++) {
        cur[p] = cyfra;

        int nowa_suma4 = suma4;
        if (p < 4) {
            nowa_suma4 += cyfra - '0';
        }

        int nowa_np_suma = np_suma;
        int nowa_p_suma = p_suma;
        if (p % 2 == 0) {
            nowa_np_suma += cyfra - '0';
        } else {
            nowa_p_suma += cyfra - '0';
        }

        int nowy_ile3 = ile3;
        int nowy_ile7 = ile7;
        if (cyfra == '3') {
            nowy_ile3++;
        } else {
            nowy_ile3 = 0;
        }
        if (cyfra == '7') {
            nowy_ile7++;
        } else {
            nowy_ile7 = 0;
        }

        printf("Generowanie liczby: %s\n", cur); // Debugowanie
        generuj_liczby(cur, p + 1, dl, nowa_suma4, nowa_np_suma, nowa_p_suma, nowy_ile3, nowy_ile7, ile, x, y);
    }
}

int main() {
    long long x, y;
    scanf("%lld %lld", &x, &y);

    int ile = 0;
    char cur[MAX_CYFRY + 1];

    for (int dl = 1; dl <= MAX_CYFRY; dl++) {
        printf("Generowanie liczb o dlugosci: %d\n", dl); // Debugowanie
        generuj_liczby(cur, 0, dl, 0, 0, 0, 0, 0, &ile, x, y);
    }

    printf("%d\n", ile);
    return 0;
}