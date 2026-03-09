/*Zadanie 2 (10 pkt.). Napisz program, który dla zadanej na wejściu naturalnej liczby N ≥ 12 odpowie na pytanie: dla jakiej liczby naturalnej M ≤ N jest najwięcej trójkątów pitagorejskich (tj. prostokątnych o bokach całkowitej długości) o obwodzie M, i ile jest tych trójkątów?

Jeśli to maksimum osiągane jest dla kilku liczb M, wypisz dowolną z nich. Dla N = 1000 maksimum wynosi 8 i osiągane jest tylko dla liczby 840, a obliczenia raczej naiwnego programu wykonywane są na przeciętnym komputerze w mgnieniu oka, więc to nie jest zadanie na nie wiadomo jakie boksowanie się z matematyką. (Ale zawsze można się chwilę poboksować i wymyślić ciekawsze rozwiązanie, czemu nie.)
*/

#include <stdio.h>
int ind = 0;

int maxM(int t[], int n) {
	int maxx = 0;
	for (int i = 0; i < n; i++) {
		if (t[i] > maxx) {
			maxx = t[i];
			ind = i;
		}
	}
	return maxx;
}

int main() {
	int M, N = 1000, a, b, c;
	//scanf("%d", N);
	int t[1000000];

	for (int i = 0; i < N; i++) {
		t[i] = 0;	
	}

	for (int k = 12; k < N + 1; k++) {
		M = k;
		for (int i = 1; i < M - 1; i++) {
			a = i;
			for (int j = 1; j < M - a; j++) {
				b = j;
				c = M - a - b;
				if (a * a + b * b == c * c) t[M - 1]++;
			}
		}
		t[k - 1] /= 2;
	}

	printf("%d", maxM(t, N));
	printf("\n");
	printf("%d", ind + 1);
	printf("\n");
	/*

		for (int i = 0; i < N; i++) {
		printf("%d", t[i]);
		printf("\n");
	}
	*/
}