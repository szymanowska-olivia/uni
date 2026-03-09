/*Żarówki
W jaskini znajduje się n² żarówek, uporządkowanych w siatkę n na n.

Każda żarówka powoli gromadzi energię i na moment rozbłyska, gdy osiągnie odpowiedni stan.

Na przykład:
5483143223
2745854711
5264556173
6141336146
6357385478
4167524645
2176841721
6882881134
4846848554
5283751526

Poziom energii każdej żarówki to wartość od 0 do 9. Żarówka w lewym górnym rogu ma poziom energii 5, ta w prawym dolnym rogu ma poziom energii 6, i tak dalej. Możesz modelować poziomy energii i rozbłyski światła w krokach.

Podczas pojedynczego kroku zachodzi następująca sekwencja: 1. Najpierw poziom energii każdej żarówki zwiększa się o 1. 2. Następnie każda żarówka z poziomem energii większym niż 9 rozbłyska.

To zwiększa poziom energii wszystkich sąsiednich żarówek o 1 (włączając żarówki położone po przekątnej). Jeśli to powoduje, że żarówka osiąga poziom energii większy niż 9, ona również rozbłyska. Ten proces trwa tak długo, jak nowe żarówki przekraczają poziom energii 9 (żarówka może rozbłysnąć co najwyżej raz na krok). Na koniec, każda żarówka która rozbłysła podczas tego kroku ma swój poziom energii ustawiony na 0, ponieważ zużyła na to całą swoją energię.

Sąsiednie rozbłyski mogą spowodować, że żarówka rozbłyśnie w danym kroku, nawet jeśli zaczyna ten krok z bardzo małą ilością energii. Rozważ środkową żarówkę z energią 1 w tej sytuacji:

Stan początkowy:
11111
19991
19191
19991
11111

Po kroku 1:
34543
40004
50005
40004
34543

Po kroku 2:
45654
51115
61116
51115
45654

Twoim zadaniem jest napisać program, który obliczy ilość rozbłysków po m krokach.

Dane wejściowe:
n m
c₀,₀ c₀,₁ ... c₀,ₙ₋₁
c₁,₀ c₁,₁ ... c₁,ₙ₋₁
...
cₙ₋₁,₀ cₙ₋₁,₁ ... cₙ₋₁,ₙ₋₁

ograniczenia na dane:
n<50
m<20000000
n*m<50000000

Przykład 1:
5 3
11111
19991
19191
19991
11111

Odpowiedź:
9

Przykład 2:
10 10
5483143223
2745854711
5264556173
6141336146
6357385478
4167524645
2176841721
6882881134
4846848554
5283751526

Odpowiedź:
204

Przykład 3:
10 100
5483143223
2745854711
5264556173
6141336146
6357385478
4167524645
2176841721
6882881134
4846848554
5283751526

Odpowiedź:
1656*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 50 
#define MAX_ENERGIA 9  
#define LICZBA_KIERUNKOW 8 

int zarowki[MAX_N][MAX_N];
int n, m;
const int dx[LICZBA_KIERUNKOW] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[LICZBA_KIERUNKOW] = {-1, 0, 1, -1, 1, -1, 0, 1};

int krok() {
    int rozblyski = 0;
    bool rozblysniete[MAX_N][MAX_N] = {false}, blysk = true;;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) zarowki[i][j]++;
    }
    while (blysk) {
        blysk = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (zarowki[i][j] > MAX_ENERGIA && !rozblysniete[i][j]) {
                    rozblysniete[i][j] = true;
                    rozblyski++;
                    //printf("%d\n", rozblyski);
                    blysk = true;

                    for (int d = 0; d < LICZBA_KIERUNKOW; d++) {
                        int ni = i + dx[d];
                        int nj = j + dy[d];

                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && !rozblysniete[ni][nj]) zarowki[ni][nj]++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (rozblysniete[i][j]) zarowki[i][j] = 0;
        }
    }
    return rozblyski;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) scanf("%1d", &zarowki[i][j]);
    }

    int suma = 0;

    for (int step = 0; step < m; step++) {
        suma += krok();
        if (suma == n * n * (step + 1)) break;
    }

    printf("%d\n", suma);
    return 0;
}
