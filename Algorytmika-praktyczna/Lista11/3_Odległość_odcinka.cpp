/*
Dane jest Q zapytań składających się z trzech punktów na płaszczyźnie p1, p2 oraz q.

Twoim zadaniem jest dla każdego zapytania policzyć jaka jest odległość punktu q od prostej przechodzącej przez punkty p1 oraz p2.
*/
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int Q, N = 3;
    cin >> Q;

    vector<pair<long long, long long>> coordinates(N + 1);


    long long x1, y1, x2, y2; 
    long long P = 0; 
    
    while (Q--){

        P = 0;
        cin >> coordinates[1].first >> coordinates[1].second;
        
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

        //string half = (P%2) == 0 ? ".0" : ".5" ;
        //cout << abs(P)/2<< half << "\n";

        double a = sqrt(((coordinates[2].first - coordinates[1].first) * (coordinates[2].first - coordinates[1].first)) + ((coordinates[2].second - coordinates[1].second) * (coordinates[2].second - coordinates[1].second)));
        double h = abs(P)/a;

       //cout << a << " ";
        cout << fixed << setprecision(9)<< h << "\n";
    } 
}
