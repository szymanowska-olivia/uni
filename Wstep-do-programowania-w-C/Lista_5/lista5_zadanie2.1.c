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
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char* argv[]) {
	int n = 80;
	if (argc > 1) {
		n = atoi(argv[1]);
		if (n < 1 || n>2) {
			printf("BLAD\n");
			return 1;
		}
	}

	srand(time(NULL));

	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		int a = rand() % 4;
		double x = (sin(i) + pow(2, a)) * pow(-1, a);
		if (x == (int)x)  printf("%d\n", (int)x);
		else printf("%.2f\n", x);
	}

	return 0;
}
