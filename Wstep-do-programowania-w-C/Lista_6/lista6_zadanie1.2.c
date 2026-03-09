/*B. Napisz program wyszukujący wzorzec w binarnym tekście (tj. nad dwuelementowym alfabetem {0, 1}). Powinien on wczytać ze standardowego wejścia dwa ciągi zerojedynkowe (podane w osobnych wierszach). Pierwszy ciąg, o długości co najwyżej 60 znaków, to wzorzec, którego wszystkie wystąpienia chcemy znaleźć w drugim ciągu. Program powinien wypisać indeksy początków wszystkich wystąpień wzorca w tekście (tj. drugim ciągu). Sprawdzenie pojedynczej pozycji należy wykonać w czasie niezależnym od długości wzorca (nie należy zatem porównywać znak po znaku, tj. bit po bicie).

Możemy traktować wzorzec jako liczbę, np. 0110 to 6, i przechodząc przez tekst rozważać każde okienko sąsiednich czterech (w tym przypadku) znaków jako liczbę, którą należy porównać ze wzorcem. Nietrudno przesuwać się pomiędzy kolejnymi okienkami – wystarczy przesunięcie bitowe (które zgubi najstarszy bit, ale to dobrze) i dopisanie jednego bitu w najmniej znaczącej pozycji. Możemy zatem przy pomocy kilku operacji utrzymywać reprezentację liczbową dla przesuwającego się okienka odpowiedniej długości bitów w tekście.

Przykładowo, dla wejścia

010
101010110101110101010111

należy wypisać

1 3 8 14 16 18

(wystąpienia indeksujemy oczywiście od zera).

Uwaga: w tym zadaniu (także w części A) należy użyć operatorów bitowych, np. przesunięć i bitowego AND zamiast (reszty z) dzielenia przez 2. Pliki źródłowe przesłane na SKOS powinny nazywać się 6.1zbior.c i 6.1wzorzec.c.*/
#include <stdio.h>
#include <string.h>

int main() {
    char wzorzec[60], ciag[60];
    int w = 0, c = 0;

    scanf("%s%s", wzorzec, ciag);

    for (int i = 0; i < strlen(wzorzec); i++) w = (w << 1) | (wzorzec[i] - '0');

    for (int i = 0; i < strlen(ciag) - strlen(wzorzec) + 1; i++) {
        c = 0;
        for (int j = 0; j < strlen(wzorzec); j++) c = (c << 1) | (ciag[j + i] - '0');
        if (w == c) printf("%d ", i);
    }

    //printf("%d\n",ile);

    return 0;
}
