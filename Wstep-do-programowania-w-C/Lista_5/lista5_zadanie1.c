
/*Zadanie 1 (10 pkt. na pracowni, później 5 pkt.). Napisz funkcję, która przyjmie jako argument tablicę liczb typu double (wraz z jej długością), znajdzie maksimum, minimum, i średnią arytmetyczną jej zawartości, i zapisze je w pozycjach, do których wskaźniki zostały podane jako trzy kolejne argumenty. Gdy tablica jest długości 0 (co w C jest zresztą, w ścisłym sensie, niemożliwe), działanie może być dowolne.

Napisz dwie funkcje, które przyjmą jako argument napis oraz znak i zwrócą wskaźnik na pozycję w zadanym napisie, która odpowiada najwcześniejszemu bądź najpóźniejszemu wystąpieniu zadanego znaku; jeśli znak nie występuje w napisie, należy zwrócić NULL (zdefiniowane w wielu nagłówkach, m.in. stdlib.h).

Napisz cztery funkcje, które przyjmą jako argument napis i zmodyfikują jego zawartość

zamieniając wszystkie litery na wielkie,
zamieniając wszystkie litery na małe,
zamieniając go na tzw. titlecase, tj. wszystkie litery bezpośrednio po białym znaku (bądź na początku napisu) na wielkie, a pozostałe – na małe,
odwracając go (najlepiej używając tylko stałej dodatkowej pamięci).
(Z tych samych powodów, co wzmiankowane na wykładzie, tych funkcji nie będzie dało się poprawnie wywołać na literałach napisowych – do testów będzie należało stworzyć napisy typu char ...[]. Wykorzystaj funkcje z ctype.h.)

W funkcji main umieść wywołania demonstrujące działanie powyższych funkcji. Czy te funkcje można jakoś składać? Co zrobić, żeby było to możliwe (na więcej sposobów)?

*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

void funkcja1(double* tab, int n, double* a, double* b, double* c) {
	int m = INT_MAX;
	int mx = INT_MIN;
	int suma = 0, srednia = 0;
	for (int i = 0; i < n; i++) {
		if (tab[i] < m) m = tab[i];
		else if (tab[i] > mx) mx = tab[i];
		suma += tab[i];
	}
	srednia = suma / n;

	*a = m;
	*b = mx;
	*c = srednia;
}

//zadania z drugiego akapitu z listy

char* funkcja2(const char* s, char c) {
	while (*s) { // Przechodzimy przez napis
		if (*s == c) {
			return (char*)s; // Zwracamy wska?nik na pozycj?
		}
		s++;
	}
	return NULL; // Je?li znak nie zosta? znaleziony
}


char* funkcja3(const char* s, char c) {
	const char* ostatni = NULL;
	while (*s) {
		if (*s == c) ostatni = s;
		s++;
	}
	return (char*)ostatni;

}


//zadania z 3 akapitu

void funkcja4(char* s) {

	while (*s) {
		*s = toupper(*s);
		s++;
	}
}

void funkcja5(char* s) {
	while (*s) {
		*s = tolower(*s);
		s++;
	}
}

void funkcja6(char* s) {
	*s = toupper(*s);
	s++;
	while (*s) {
		if (isspace(*s)) {
			s++;
			*s = toupper(*s);
			s++;
		}
		else {
			*s = tolower(*s);
			s++;
		}
	}
}
void funkcja7(char* s) {
	char* i = s;
	char* j = s + strlen(s) - 1;
	while (i < j) {
		char pom = *i;
		*i = *j;
		*j = pom;
		i++;
		j--;
	}
}


int main(int argc, char* argv[]) {

	double t[9] = { 1,2,3,4,5,6,7,8,9 }, a = 0, b = 0, c = 0;
	int n = 9;
	char s[11] = "Hello World";
	char r = 'o';

	funkcja1(t, n, &a, &b, &c);
	printf("funkcja1: %f,%f,%f\n", a, b, c);

	printf("funkcja2: %ld\n", funkcja2(s, r) - s);

	printf("funkcja3: %ld\n", funkcja3(s, r) - s);

	funkcja4(s);
	printf("funkcja4: %s\n", s);

	funkcja5(s);
	printf("funkcja5: %s\n", s);

	funkcja6(s);
	printf("funkcja6: %s\n", s);

	funkcja7(s);
	printf("funkcja7: %s\n", s);

	return 0;
}