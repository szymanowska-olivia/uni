/*Zadanie 2 (10 pkt.). Napisz program, który dla zadanej w parametrach wywołania programu kwoty w złotych rozmieni ją na jak najmniejszą liczbę monet o nominałach: 5 zł, 2 zł, 1 zł, 50 gr, 20 gr, 10 gr, 5 gr, 2 gr, 1 gr. Program powinien wypisać "BLAD" w przypadku podania nieprawidłowego argumentu.

Uwaga: obliczenia należy wykonywać w groszach na liczbach całkowitych – typy zmiennopozycyjne niekoniecznie się do tego nadają (np. 0,1 to binarnie 0,0001100110011(0011)). Co za tym idzie, argument najlepiej przekonwertować na grosze samemu (lub używając funkcji bibliotecznych, ale nie przez proste, pojedyncze wywołanie atof(argv[1])). Należy uwzględnić również to, że separatorem dziesiętnym może być zarówno kropka, jak i przecinek.

Dla argumentu 10,75 wyjściem będzie

2x5zl
1x50gr
1x20gr
1x5gr
Argumenty takie jak Ala, -5 czy 31.337 są błędne, ale 0 jest poprawny (wtedy wyjście będzie puste).*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("BLAD \n");
        return 0;
    }

    int l = strlen(argv[1]);
    int poprzecinku = 0;
    int nominaly[] = { 500, 200, 100, 50, 20, 10, 5, 2, 1 };
    const char* nazwy[] = { "5zl", "2zl", "1zl", "50gr", "20gr", "10gr", "5gr", "2gr", "1gr" };
    bool kropka = false;


    for (int i = 0; i < l; i++) {
        if (argv[1][i] == ',' || argv[1][i] == '.') {
            if (kropka) {
                printf("BLAD \n");
                return 0;
            }
            argv[1][i] = '.';
            kropka = true;
        }
        else if (!isdigit(argv[1][i])) {
            printf("BLAD \n");
            return 0;
        }
        else if (kropka) {
            poprzecinku++;
            if (poprzecinku > 2) {
                printf("BLAD \n");
                return 0;
            }
        }

    }

    double kwota = atof(argv[1]);

    if (kwota < 0) {
        printf("BLAD \n");
        return 0;
    }

    int kwgr = kwota * 100, ilosc = 0;

    for (int i = 0; i < 9; i++) {
        ilosc = kwgr / nominaly[i];
        if (ilosc > 0) {
            printf("%dx%s\n", ilosc, nazwy[i]);
            kwgr -= ilosc * nominaly[i];
        }
    }

    return 0;
}