/*Proste Zadanie 2 na nadchodzące Mikołajki (10 pkt.). Sumę n kolejnych liczb naturalnych nazywamy n-tą liczbą trójkątną (bo jest to liczba kulek ciasno upakowanych w trójkąt równoboczny o boku n). Przykładowo, siódma liczba trójkątna to 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28.

Dodatkowo, okazuje się ona być najwcześniejszą liczbą trójkątną, która ma więcej niż pięć dzielników (bo ma ich sześć: 1, 2, 4, 7, 14 i 28); wcześniejsze liczby trójkątne wraz z ich dzielnikami to kolejno:

1 podzielne przez 1;
3 podzielne przez 1 i 3;
6 podzielne przez 1, 2, 3 i 6;
10 podzielne przez 1, 2, 5 i 10;
15 podzielne przez 1, 3, 5 i 15;
21 podzielne przez 1, 3, 7 i 21.
Napisz program, który wydrukuje indeks i wartość najwcześniejszej liczby trójkątnej, która ma więcej niż N dzielników; N odczytaj z jedynego obowiązkowego argumentu wywołania. Wykorzystaj do tego funkcję biblioteczną strtoul.h – w celu skontrolowania poprawności podaj jej nietrywialny drugi argument po to, żeby móc sprawdzić, czy konwersja "dojechała" do końca napisu.

Przetestuj swój program dla argumentów 100, 200, 300.*/
#include <stdio.h>
#include <stdlib.h>

unsigned long dzielniki(int n) {
    if (n == 1) return 1;
    if (n == 0) return 0;

    int ile = 2;

    for (int i = 2; i * i <= n; i++) {
        if (i * i == n) ile++;
        else if (n % i == 0) ile += 2;
    }

    return ile;
}

int main(int argc, char* argv[])
{
    char* end;

    if (argc != 2) {
        printf("BLAD\n");
        return 1;
    }

    unsigned long N = strtoul(argv[1], &end, 10);

    if (*end != '\0') {
        printf("BLAD\n");
        return 1;
    }

    unsigned long l = N, d;
    unsigned long long t = (l * (l + 1)) / 2;

    while (1) {
        d = dzielniki(t);
        if (d > N) {
            printf("%lu %llu", l, t);
            break;
        }
        l++;
        t += l;
    }

    return 0;
}