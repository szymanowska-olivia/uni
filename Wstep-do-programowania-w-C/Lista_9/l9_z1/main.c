/*Napisz program, który wczyta do pamięci całą zawartość ze standardowego wejścia, posortuje jej wiersze w pewien dziwaczny sposób, i wypisze efekt na standardowe wyjście.

Zakładamy, że wiersze kończą się pojedynczym znakiem '\n' (bądź EOF), a słowa składają się wyłącznie ze znaków "graficznych" (tj. drukowalnych, ale nie białych, użyj isgraph z ctype.h). Pozostałe znaki (tj. białe i kontrolne) rozdzielają słowa; w przetwarzaniu będziemy je ignorować, a na wyjściu zamiast ich bloków będziemy drukować pojedyncze spacje. Nie uwzględniamy pustych słów, za to uwzględniamy puste wiersze (kiedy pomiędzy dwoma znakami '\n' znajdują się tylko znaki białe i kontrolne, albo w ogóle żadne).

Kryterium porządkowania wierszy to zwykły porządek słownikowy, ale dla odwróconej kolejności słów w wierszu: wiersz "aaa zzx" jest późniejszy niż "bbb yyz". Kolejność liter w słowach pozostaje niezmieniona, tj. składające się z jednego słowa wiersze "abcd" i "dcba" pozostają w "normalnym" porządku.

Żeby móc uporządkować wiersze według tego kryterium, a potem wydrukować je "normalnie", spamiętaj wejście w następującej strukturze:

wiersz zareprezentuj jako tablicę napisów (słów); do Twojej decyzji należy, czy zapamiętasz też gdzieś jej długość, czy umieścisz w niej wartownika (np. NULL);
całe wejście oczywiście zareprezentuj jako tablicę wierszy jw., będzie więc ona miała typ char *** (chyba że postanowisz wiersze poukrywać w jakichś structach).
Wczytywanie pojedynczego wiersza powinno odbywać się w osobnej funkcji; jej sygnatura jest do Twojej decyzji w zależności od potrzeb, ale jeśli będzie inna niż char * readline(), wyjaśnij znaczenie argumentów w komentarzu dokumentacyjnym. Może to być zresztą wskazane z praktycznych powodów – jeśli chcesz, by kolejne wywołania tej funkcji używały tego samego, już wcześniej zaalokowanego bufora itp., to należy go im jakoś przekazać. Nie rób żadnych założeń co do długości wczytywanych wierszy – jeśli brakuje Ci miejsca, zrealokuj bufor (np. prosząc o dwa razy więcej pamięci, niż było w nim dotychczas).

Do porównywania wierszy zgodnie z ww. porządkiem napisz komparator, który będzie zwracał –1, jeśli pierwszy argument jest wcześniejszy niż drugi, 1 jeśli jest późniejszy, i 0 jeśli są równe. Komparator może używać strcmp, ale lepiej wywołać ją wiele razy dla poszczególnych słów w porównywanych wierszach, zamiast sklejać te słowa w pojedynczy napis tylko po to, żeby wywołać strcmp raz.

Napisz plik nagłówkowy, w którym zadeklarujesz funkcję sortującą przyjmującą tablicę wierszy (czyli oczywiście wskaźnik na jej pierwszy element), ich liczbę, oraz wskaźnik na funkcję porównującą. Plik z implementacją tej funkcji napisz (przy użyciu instrukcji warunkowych preprocesora) tak, by:

przy kompilacji z flagą -DUSE_QSORT funkcja sortująca była tylko wrapper-em na qsort z stdlib.h, któremu przekaże swoje argumenty (oraz odpowiednią wartość rozmiaru komórki tablicy w trzeciej pozycji) – użyj do tego dyrektywy #ifdef USE_QSORT;
w przeciwnym przypadku zaimplementuj algorytm prostego sortowania, który wykorzysta komparator przekazany jako argument; algorytm wybierz w zależności od reszty z dzielenia Twojego numeru indeksu przez 3 (0 – sortowanie bąbelkowe, 1 – sortowanie przez wstawianie, 2 – sortowanie przez wybór), umieść tę informację również w komentarzu.
Użycie qsort może wymusić zadeklarowanie komparatora z kwalifikatorem typu const dla argumentów, co w konsekwencji sprawi, że komparator nie będzie mógł modyfikować stanu swoich argumentów (ale i tak nie powinien, w końcu ma je tylko porównać, a nie zmieniać). Ten mechanizm będzie jeszcze omawiany na najbliższym wykładzie. M.in. dlatego warto najpierw napisać wersję z qsort (i dopasować wszystkie deklaracje), a dopiero potem zaimplementować własne sortowanie, żeby ono też było z nimi zgodne.

Proste sortowanie możesz spróbować zaimplementować tak, by jego sygnatura była równie "generyczna" jak dla qsort (wtedy warto to zrobić w kolejnej funkcji, a ww. funkcja będzie wyłącznie wrapper-em na jedno lub drugie sortowanie generyczne), ale gdyby były z tym podejściem jakieś problemy, możesz odłożyć to podejście na później. Zauważ, że jeśli nie zdążysz lub nie będziesz mieć ochoty zaimplementować prostego sortowania, to cała reszta zadania może być dalej implementowana i testowana dzięki kompilacji z -DUSE_QSORT.

Struktura logiczna całego programu powinna być taka:

dopóki jest coś na wejściu:
wczytaj cały wiersz przy użyciu przeznaczonej do tego funkcji
podziel go na słowa i umieść w "głównej" tablicy, być może ją realokując, jeśli skończyło się w niej miejsce
wywołaj funkcję sortującą, z "główną" tablicą i własnym komparatorem jako argumentami
wypisz zawartość posortowanej "głównej" tablicy, wstawiając pojedyncze spacje pomiędzy słowa i pojedyncze znaki '\n' pomiędzy wiersze
Zarówno w funkcji wczytującej wiersze, jak i podziale wiersza na słowa może wystąpić niepowodzenie alokacji pamięci. W takiej sytuacji przerwij wczytywanie, a następnie posortuj i wypisz te wiersze, które udało się wczytać (natomiast pamięć zajęta przez ew. ostatni, częściowo wczytany wiersz, powinna zostać od razu zwolniona). W trakcie wypisywania zwalniaj pamięć zajmowaną przez słowa i wiersze najwcześniej, jak się da (tj. od razu po ich wypisaniu).*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funkcje.h"

#define ROZMIAR_BUFORU 128
#define POJ_WIERSZY 10

char *czytaj(FILE *wejscie) {
    size_t rozmiar = ROZMIAR_BUFORU;
    size_t dlugosc = 0;
    char *bufor = malloc(rozmiar);
    if (!bufor) return NULL;

    int c;
    while ((c = fgetc(wejscie)) != EOF) {
        if (dlugosc + 1 >= rozmiar) {
            rozmiar *= 2;
            char *nowy_bufor = realloc(bufor, rozmiar);
            if (!nowy_bufor) {
                free(bufor);
                return NULL;
            }
            bufor = nowy_bufor;
        }
        bufor[dlugosc++] = (char)c;
        if (c == '\n') break;
    }

    if (dlugosc == 0 && c == EOF) {
        free(bufor);
        return NULL;
    }

    bufor[dlugosc] = '\0';
    return bufor;
}

char **rozbij_na(const char *wiersz) {
    size_t pojemnosc = 10;
    size_t liczba = 0;
    char **slowa = malloc(pojemnosc * sizeof(char *));
    if (!slowa) return NULL;

    const char *poczatek = wiersz;
    while (*poczatek) {
        while (*poczatek && !isgraph((unsigned char)*poczatek)) poczatek++;

        if (*poczatek) {
            const char *koniec = poczatek;
            while (*koniec && isgraph((unsigned char)*koniec)) koniec++;

            size_t dlugosc_slowa = koniec - poczatek;
            char *slowo = malloc(dlugosc_slowa + 1);
            if (!slowo) {
                for (size_t i = 0; i < liczba; i++) free(slowa[i]);
                free(slowa);
                return NULL;
            }

            strncpy(slowo, poczatek, dlugosc_slowa);
            slowo[dlugosc_slowa] = '\0';

            if (liczba >= pojemnosc) {
                pojemnosc *= 2;
                char **nowe_slowa = realloc(slowa, pojemnosc * sizeof(char *));
                if (!nowe_slowa) {
                    for (size_t i = 0; i < liczba; i++) free(slowa[i]);
                    free(slowa);
                    return NULL;
                }
                slowa = nowe_slowa;
            }

            slowa[liczba++] = slowo;
            poczatek = koniec;
        }
    }

    slowa[liczba] = NULL;
    return slowa;
}

void wypisz(char **slowa) {
    if (!slowa || !*slowa) {
        printf("\n");
        return;
    }

    for (size_t i = 0; slowa[i]; i++) {
        if (i > 0) printf(" ");
        printf("%s", slowa[i]);
    }
    printf("\n");
}

void zwolnij(char **slowa) {
    if (!slowa) return;
    for (size_t i = 0; slowa[i]; i++) free(slowa[i]);
    free(slowa);
}

int porownaj(const void *a, const void *b) {
    char **wiersz_a = *(char ***)a;
    char **wiersz_b = *(char ***)b;

    size_t i = 0, j = 0;
    while (wiersz_a[i]) i++;
    while (wiersz_b[j]) j++;

    while (i > 0 && j > 0) {
        int cmp = strcmp(wiersz_a[--i], wiersz_b[--j]);
        if (cmp != 0) return cmp;
    }

    return (i == 0 && j == 0) ? 0 : (i == 0 ? -1 : 1);
}

int main() {
    char ***wiersze = malloc(POJ_WIERSZY * sizeof(char **));
    if (!wiersze) {
        fprintf(stderr, "Nie udało się przydzielić pamięci\n");
        return 1;
    }

    size_t liczba_wierszy = 0;
    size_t pojemnosc_wierszy = POJ_WIERSZY;

    char *wiersz;
    while ((wiersz = czytaj(stdin)) != NULL) {
        if (liczba_wierszy >= pojemnosc_wierszy) {
            pojemnosc_wierszy *= 2;
            char ***nowe_wiersze = realloc(wiersze, pojemnosc_wierszy * sizeof(char **));
            if (!nowe_wiersze) {
                fprintf(stderr, "Nie udało się przydzielić pamięci\n");
                free(wiersz);
                break;
            }
            wiersze = nowe_wiersze;
        }

        wiersze[liczba_wierszy] = rozbij_na(wiersz);
        free(wiersz);
        if (!wiersze[liczba_wierszy]) break;
        liczba_wierszy++;
    }

    sort_w(wiersze, liczba_wierszy, porownaj);

    for (size_t i = 0; i < liczba_wierszy; i++) {
        wypisz(wiersze[i]);
        zwolnij(wiersze[i]);
    }
    free(wiersze);

    return 0;
}
