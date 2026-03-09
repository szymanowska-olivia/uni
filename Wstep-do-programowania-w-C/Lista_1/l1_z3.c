/*Generowanie ciągu
Dana jest liczba n (nie większa od miliona) oraz n-1 zależności w postaci ,,-1'' lub ,,1''. Chcemy na tej podstawie zbudować n-elementowy ciąg, zgodnie z następującymi zasadami:

wszystkie liczby w ciągu muszą być naturalne dodatnie,
jeżeli i-ta zależność to „-1” liczba na pozycji i musi być większa niż liczba na pozycji i+1 (ciąg jest w tym miejscu rosnący),
jeżeli i-ta zależność to „1”, liczba na pozycji i musi być mniejsza niż liczba na pozycji i+1 (ciąg jest w tym miejscu malejący),
suma elementów ciągu musi być jak najmniejsza.
Wejście
W pierwszej linii wejścia znajduje się dodatnia liczba naturalna n ≤ 1000000. Druga linia wejścia składa się z n-1 oddzielonych spacjami 1 i -1.

Wyjście
Jedyna linia wyjścia powinna składać się z n oddzielonych spacjami liczb naturalnych dodatnich tworzących ciąg zgodnie z zasadami zadania.

Przykłady
A
Wejście:

5

-1 1 1 1

Wyjście

2 1 2 3 4

B
Wejście:

12

-1 -1 1 -1 -1 1 1 1 -1 -1 -1

Wyjście

3 2 1 3 2 1 2 3 4 3 2 1

C
Wejście

2

1

Wyjście

1 2*/

#include <stdio.h>

int main() {
    int n,b[1000000],t[1000000];
    
    scanf("%d",&n);
    for (int i=0;i<n-1;i++) {
        scanf("%d",&b[i]);
        t[i]=1;
    }
    
    t[n-1]=1;



    for (int i=0;i<n-1;i++) {
        if (b[i]==1) t[i+1]=t[i]+1;
        
    }
    for (int i=n-2;i>-1;i--) {
        if (b[i]==-1&&t[i]<t[i+1]+1) t[i]=t[i+1]+1;
    }


    for (int i=0;i<n;i++) {
        printf("%d ",t[i]);
    }

    return 0;
}
