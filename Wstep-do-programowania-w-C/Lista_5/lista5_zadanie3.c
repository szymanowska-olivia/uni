/*Dane są liczby n i m oraz posadzka składająca się z kwadratowych kafelków w m kolumnach i n wierszach. Na każdym kafelku stoi liczba naturalna oznaczająca karę za pobrudzenie ubłoconym obuwiem świeżo mytego kafelka.

Zaczynamy na lewo od pierwszej kolumny kafelków i przechodzimy przez posadzkę, robiąc kroki zawsze o 1 kolumnę w prawo, albo pozostając w tym samym wierszu, albo zmieniając go na sąsiedni (powyżej lub poniżej); w pierwszym kroku możemy wejść na dowolny kafelek w pierwszej kolumnie. Chcemy przejść przez posadzkę na jej prawą stronę, płacąc możliwie małą karę.

Wejście
W pierwszej linii wejścia znajdują się liczby n i m, n nie większe od 1000.

W każdej z kolejnych n linii wejścia znajduje się m liczb naturalnych, nie większych od 1000. Stanowią one wartości kar odpowiadających kolejnym kafelkom w danym wierszu.

Wyjście
Na wyjściu powinna się pojawić jedna liczba naturalna oznaczająca minimalną karę, jaką należy zapłacić.

Przykłady
A
Wejście:

2 3
1 2 3
2 1 5

Wyjście

5

(Optymalne jest przejść przez kafelki o karach 1, 1, 3)

B
Wejście:

2 3
1 7 9
2 8 4

Wyjście

12

C
Wejście:

3 4
1 1 1 1
2 3 1 7
1 1 2 8

Wyjście

4*/
#include <stdio.h>
#include <limits.h>

#define MAX_N 1000

int najmniejsza_kara(int t[MAX_N][MAX_N], int n, int m) {
	int tab[MAX_N][MAX_N];

	for (int i = 0; i < n; i++) tab[i][0] = t[i][0];

	for (int j = 1; j < m; j++) {
		for (int i = 0; i < n; i++) {
			int here = tab[i][j - 1];
			int up = (i > 0) ? tab[i - 1][j - 1] : INT_MAX;
			int down = (i < n - 1) ? tab[i + 1][j - 1] : INT_MAX;

			int mini = (here < up ? (here < down ? here : down) : (up < down ? up : down));

			tab[i][j] = t[i][j] + mini;
		}
	}

	int MINI = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (tab[i][m - 1] < MINI) MINI = tab[i][m - 1];
	}

	return MINI;
}

int main() {
	int n, m, t[MAX_N][MAX_N];

	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) scanf("%d", &t[i][j]);
	}

	printf("%d\n", najmniejsza_kara(t, n, m));

	return 0;
}
