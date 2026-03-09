/*Zadanie 1 (10 pkt. na pracowni, później 5 pkt.). Napisz program, który dla podanego w parametrach wywołania programu ciągu znaków przedstawi efekt meksykańskiej fali (jeden cykl). Zasady:

Załóż, że ciąg wejściowy składa się tylko z liter lub spacji, ale może być pusty.
Program ma zademonstrować efekt fali, wypisując w kolejnych liniach (po jednej dla każdego znaku będącego literą) kolejne etapy procesu.
Wielka litera reprezentuje osobę stojącą, mała – siedzącą.
Jeśli znak w ciągu jest spacją, należy go pominąć w kolejnych transformacjach napisu tak, jakby było to puste miejsce (ale nadal należy go wydrukować).
Przykładowo, dla argumentu

Witaj Swiecie
należałoby wypisać

Witaj swiecie
wItaj swiecie
wiTaj swiecie
witAj swiecie
witaJ swiecie
witaj Swiecie
witaj sWiecie
witaj swIecie
witaj swiEcie
witaj swieCie
witaj swiecIe
witaj swieciE
a dla

ab  CD
wyjście to

Ab  cd
aB  cd
ab  Cd
ab  cD
Uwaga: aby wprowadzić jako jeden argument wywołania napis zawierający spacje, należy go otoczyć cudzysłowami. Zostaną one zinterpretowane przez powłokę (linię poleceń) i same nie zostaną przekazane jako część argumentu. Podobnie można przekazać pusty napis jako argument – wywołania dla powyższych przykładów oraz dla pustego napisu wyglądałyby odpowiednio

./a.out "Witaj Swiecie"
./a.out "ab  CD"
./a.out ""
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    int l = 0;
    char tab[100000];
    bool spacja = false;

    if (argc <= 1)
        return 0;

    l = strlen(argv[1]);

    printf("%d\n", l);

    for (int j = 0; j < l; j++)
    {
        spacja = false;
        for (int i = 0; i < l; i++)
        {
            tab[i] = tolower(argv[1][i]);
        }
        tab[j] = toupper(argv[1][j]);
        if (isspace(argv[1][j]))
            spacja = true;
        if (!spacja)
            puts(tab);
    }

    return 0;
}