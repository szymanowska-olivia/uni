
//w drugim podpunkcie tego zadania nie byłam pewna czy chodzi o znalezienie par liczb względnie pierwszych, nie większych niż n 
//czy liczb nie większych od n, względnie pierwszych z n 
//ostatecznie zdecydowałam się na pierwszą opcję, ale w komentarzu zostawiam drugą

#include <stdio.h>

long long gcd_rec(long long p, long long q) {
    if (q == 0) return p;
    return gcd_rec(q, p % q);
}

long long gcd_imp(long long p, long long q) {
    while (q != 0) {
        long long pom= p % q;
        p = q;
        q = pom;
    }
    return p;
}

//znajdowanie par liczb wzglednie pierwszych mniejszych od n

void wzglednie_p_rec(int p, int q, int n) {
    if (p > n) return; 
    if (q > n) wzglednie_p_rec(p + 1, p + 2, n);
    else {
        if (gcd_rec(p, q) == 1) printf("%d %d\n", p, q);
        wzglednie_p_rec(p, q + 1, n);
    }
}

void wzglednie_p_imp(long long n) {
    for(int i=1;i<n+1;i++){ 
        for(int j=i+1;j<n+1;j++)
            if (gcd_imp(i,j)==1) printf("%d %d\n",i,j);
    }
}

//znajdowanie liczb mniejszych od n, wzglednie pierwszych z n

/*
void wzglednie_p_z_n_rec(long long p, long long q) {
    if (p == 1) {
        printf("1\n");
        return;
    }
    if (gcd_rec(p, q) == 1) printf("%lld ", p);
    wzglednie_p_z_n_rec(p - 1, q);
}

long long wzglednie_p_z_n_imp(long long n) {
    for(long long i=1;i<n;i++) 
        if (gcd_imp(i,n)==1) printf("%lld ",i);
    printf("\n");
    return 0;
}
*/

int main(){
    int n;
    scanf("%d", &n);

    wzglednie_p_rec(1, 2, n);
    printf("\n");
    wzglednie_p_imp(n);
    
    //wzglednie_p_z_n_rec(n - 1, n);
    //wzglednie_p_z_n_imp(n);

    return 0;
}
