/*
Zadanie polega na policzeniu pola wielokąta o N wierzchołkach bez samoprzecięć.
*/
#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int N;
    cin >> N;

    vector<pair<long long, long long>> coordinates(N + 1);

    cin >> coordinates[1].first >> coordinates[1].second;

    long long x1, y1, x2, y2; 
    long long P = 0; 
    
    for (int i = 2; i < N + 2; i++){
        if (i != N + 1){ //W!=(N, 1)

            cin >> coordinates[i].first >> coordinates[i].second;

            x2 = coordinates[i].first, y2 = coordinates[i].second;
            x1 = coordinates[i - 1].first, y1 = coordinates[i - 1].second;

        } else{

            x2 = coordinates[1].first, y2 = coordinates[1].second;
            x1 = coordinates[N].first, y1 = coordinates[N].second;
        }

        P += (x2 * y1) - (x1 * y2);  
    }

    string half = (P%2) == 0 ? ".0" : ".5" ;
    cout << abs(P)/2<< half << "\n";
    
}
