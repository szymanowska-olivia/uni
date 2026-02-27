/*
Dany jest ciąg N liczb całkowitych. Twoim zadaniem jest przetworzyć Q zapytań w formie:

zamień liczbę na pozycji k na wartość u,
policz sumę na przedziale [a,b].
*/
#include <iostream>
#include <vector>
#include <math.h>


using namespace std;

const int MAX_N = 200000;

void preprocess_sum(int N,vector<int> &v, vector<long long> &s){
    int block = sqrt(N);
    s.resize((N + block - 1) / block, 0);  

    for (int i = 0; i < N; i++) s[i / block] += v[i]; 
}

void swap_k_u(int N,vector<int> &v, vector<long long> &s,int k, int u){
    int block = sqrt(N);
    int pom=v[k];
    v[k]=u;
    int i=k/block;
    s[i]-=pom;
    s[i]+=u;
}

long long sum_a_b(int N,vector<int> &v, vector<long long> &s,int a, int b){
    int block = sqrt(N);
    long long sum=0;
    int i=a/block, j=b/block;

    if (i == j) {  
        for (int k = a; k <= b; k++) sum += v[k];
        return sum;
    } 

    while(a%block!=0 && a <= b){
         sum+=v[a];
            a++;
    }
    while((b+1)%block!=0 && a <= b){
            sum+=v[b];
            b--;
    }
    i=a/block;
    j=b/block;
    for(int k=i;k<=j;k++) sum+=s[k];

    return sum;

}

int main(){
   int N,Q;
   cin >> N >> Q;

   vector<int> v(N);
   vector<long long> s;
   for (int i=0; i<N; i++) cin>>v[i];

    preprocess_sum(N, v, s);

   int l,x,y;
   while(Q--){
        cin>>l>>x>>y;
        x--;
        if (l==1) swap_k_u(N,v, s, x, y);
        else {y--; cout<<sum_a_b(N, v, s, x, y)<<"\n";}
   }


}