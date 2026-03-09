/*Zadanie 2 (10 pkt.). Napisz program, który wczytuje ze standardowego wejścia liczbę n ≥ 3 i następnie n liczb całkowitych. Nie używając sortowania (a najlepiej też bez tablic) wypisz 3 najmniejsze spośród tych liczb.

Następnie wypisz, która z tych trzech najmniejszych liczb ma najwięcej różnych nieparzystych czynników pierwszych w rozkładzie. Wyznaczanie liczby takich czynników powinno być realizowane w osobnej funkcji (np. wykorzystującej, z odpowiednimi modyfikacjami, kod z wykładu – rozklad_dopierwiastka.c).

Przykładowo, spośród liczb 16=2^4, 21=3×7 i 125=5^3, najwięcej różnych nieparzystych czynników pierwszych ma 21.*/

#include <stdio.h>

int najwiecejrnczynnikow(int x) {
	int y = 0;
	for (int i = 3; i < x + 1; i += 2) {
		if (x % i == 0) {
			y++;
			while (x % i == 0) {
				x /= i;
			}
		}
	}
	return y;
}

int main() {
	int n, a = 10000, b = 100000, c = 100000, l; // c to najmniejsza z 3 namjniejszych liczb,natomiast a najwieksza z nich
	int da = 0, db = 0, dc = 0, maxc, wyjscie;

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &l);
		if (l < c) {
			a = b;
			b = c;
			c = l;
		}
		else if (l < b) {
			a = b;
			b = l;
		}
		else if (l < a) a = l;
	}

	printf(" %d %d %d\n", a, b, c);

	da = najwiecejrnczynnikow(a);
	db = najwiecejrnczynnikow(b);
	dc = najwiecejrnczynnikow(c);

	printf(" %d %d %d\n", da, db, dc);

	maxc = da;
	wyjscie = a;
	if (db > maxc) { wyjscie = b; maxc = db; }
	if (dc > maxc) { wyjscie = c; maxc = dc; }

	printf(" %d", wyjscie);
}