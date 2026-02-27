/*
Dane są trzy punkty na płaszczyźnie p1 = (x1,y1), p2 = (x2,y2) oraz p3 = (x3,y3).

Twoim zadaniem jest określić czy punkt p3 leży na prostej przechodzącej przez punkty p1 i p2, a jeśli nie, to czy leży na lewo czy na prawo od niej, patrząc z punktu p1 w kierunku p2.
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

    vector<pair<long long, long long>> coordinates(4);
    long long W;

    while (N--){

    cin >> coordinates[1].first >> coordinates[1].second;
    int x, y;
    for (int i = 2; i < 4; i++){
        cin >> x >> y;
        coordinates[i].first = x - coordinates[1].first;
        coordinates[i].second = y - coordinates[1].second;
    }
    
    W = (coordinates[3].first * coordinates[2].second) - (coordinates[2].first * coordinates[3].second);  

    if (W == 0) cout << "TOUCH";
    else if (W < 0) cout << "LEFT";
    else cout << "RIGHT";
    cout << "\n";

    }
}
