/*Zwiedzanie
Na pewnej planecie znajduje się n miast, połączonych m głównymi dwukierunkowymi trasami: lotniczymi, kolejowymi i autobusowymi. Turysta Ijon Tichy nie ma zbyt wiele czasu przed kolejną podróżą międzygwiezdną, a koniecznie chciałby przetestować po jednym rodzaju połączenia. Powziął więc zamierzenie, że najpierw uda się gdzieś z miasta nr 1 samolotem, następnie wybierze pojedynczy przejazd koleją, by zakończyć podróż autobusem. Innymi słowy, chce przemieścić się z miasta nr 1 trzema połączeniami, korzystając w odpowiedniej kolejności ze wszystkich trzech środków transportu. Zastanawia go jednak, do ilu różnych miast może w ten sposób dotrzeć (przy czym nie przeszkadza mu, gdyby miał w trakcie podróży się 'cofać'). Dodatkowo, gdyby dostał wcześniejsze wezwanie do opuszczenia planety, Ijona interesuje jeszcze druga liczba - do ilu miast można dotrzeć z miasta nr 1 korzystając tylko z (nieograniczonej liczby, wliczając zero) połączeń lotniczych.

Wejście
W pierwszym wierszu wejścia znajdują się naturalne liczby 1 < n,m < 100000. W każdym z kolejnych m wierszy wejścia znajduje się ciąg x y z, gdzie x,y to liczby będące numerami dwóch różnych miast (zatem z zakresu [1,n]), a z to pojedyncza litera 'L', 'K' lub 'A', oznaczające środek transportu łączący miast o numerach x,y. Potencjalnie między dwoma miastami może występować wiele połączeń.

Wyjście
Na standardowe wyjście należy wypisać dwie oddzielone spacją liczby, będącą liczbą miast do których może dotrzeć kosmiczny turysta na wskazane sposoby.

Przykłady
Przykład A
Wejście
2 1
1 2 L

Wyjście
0 2

Na planecie brak połączeń kolejowych czy autobusowych, zatem pierwsza metoda jest niewykonalna. Da się jednak przemieścić do miast 1 i 2 za pomocą samolotu.

Przykład B
Wejście
4 3
1 2 L
2 3 K
3 4 A

Wyjście
1 2

Trasa z miasta 1 do 4 spełnia wymogi wykorzystania kolejno samolotu, pociągu i autobusu. Ponadto nadal do miast 1 i 2 można dotrzeć samolotami.

Przykład C
Wejście
5 7
1 2 L
1 2 K
1 3 L
2 4 K
3 4 K
1 5 A
2 4 A

Wyjście
2 3

Możemy dotrzeć do miast 2 i 5, wymieniając środki transportu. Miasta 1, 2 i 3 są dostępne przy użyciu jedynie samolotów.

Uwagi
Limit pamięci dla rozwiązań to 10MB.*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 100000

typedef struct Node {
    int city;
    char transport;
    struct Node *next;
} Node;

Node *adjList[MAX_N + 1] = {NULL};
bool samolotem[MAX_N + 1];

void addPolaczenie(int x, int y, char transport) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->city = y;
    newNode->transport = transport;
    newNode->next = adjList[x];
    adjList[x] = newNode;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->city = x;
    newNode->transport = transport;
    newNode->next = adjList[y];
    adjList[y] = newNode;
    printf("Debug: addPolaczenie called with x=%d, y=%d, z=%c\n", x, y, transport);
}

void dfs(int city) {
    if (samolotem[city]) return;
    samolotem[city] = true;
    for (Node *node = adjList[city]; node; node = node->next) {
        if (node->transport == 'L') dfs(node->city);
    }
}

int IleSamolotem() {
    memset(samolotem, false, sizeof(samolotem));
    dfs(1);
    int count = 0;
    for (int i = 1; i <= MAX_N; i++) if (samolotem[i]) count++;
    return count;
}

int ile_LKA() {
    bool visitedCities[MAX_N + 1] = {false};
    int count = 0;
    for (Node *node1 = adjList[1]; node1; node1 = node1->next) {
        if (node1->transport != 'L') continue;
        for (Node *node2 = adjList[node1->city]; node2; node2 = node2->next) {
            if (node2->transport != 'K') continue;
            for (Node *node3 = adjList[node2->city]; node3; node3 = node3->next) {
                if (node3->transport == 'A' && node3->city != 1 && !visitedCities[node3->city]) {
                    visitedCities[node3->city] = true;
                    count++;
                }
            }
        }
    }
    return count;
    printf("Debug: ile_LKA called\n");
}

void freeMemory(int n) {
    for (int i = 1; i <= n; i++) {
        Node *node = adjList[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            free(temp);
        }
    }
}

int main() {
    int n, m, x, y;
    char z;
    scanf("%d %d", &n, &m);

    printf("n: %d, m: %d\n", n, m); // Debug print

    for (int i = 0; i < m; i++) {
        scanf("%d %d %c", &x, &y, &z);
        printf("Adding connection: %d %d %c\n", x, y, z); // Debug print
        addPolaczenie(x, y, z);
    }

    int lka = ile_LKA();
    int samolotem = IleSamolotem();
    printf("LKA: %d, Samolotem: %d\n", lka, samolotem); // Debug print

    printf("%d %d\n", lka, samolotem);
    freeMemory(n);
    return 0;
}
