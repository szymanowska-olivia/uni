#include <iostream>

using namespace std;


int main() {

    srand(time(0));
    int N = 100000, M = 200000;
    
    cout << N<<" "<< M<<"\n";

    for(int j = 0; j < M; j++){
    for(int i = 1; i < N-1 + 1; i++) cout << rand() % N + 1<< " ";
    cout<< rand() % 10 + 1 <<"\n";
    }
    

}
