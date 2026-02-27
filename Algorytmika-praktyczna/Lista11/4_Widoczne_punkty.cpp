/*
Dany jest punkt q leżący na osi OX układu współrzędnych oraz N punktów leżących w górnej części układu współrzędnych.

Twoim zadaniem jest policzyć ile spośród tych punktów jest widocznych z punktu q. Uznajemy, że punkt p jest widoczny z q jeśli na odcinku łączącym te dwa punkty nie leży żaden inny punkt.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<long long, long long>> coordinates;

auto cmp = [](const std::pair<long long, long long>& a, const std::pair<long long, long long>& b) {

    long long W = a.first * b.second - b.first * a.second;

    if (W != 0) return W > 0;

    return a.first * a.first + a.second * a.second < b.first * b.first + b.second * b.second;
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int XP;
    cin >> XP;

    int N;
    cin >> N;

    coordinates.resize(N + 1);

    int ile = N;

    coordinates[0].first = 0, coordinates[0].second = 0;

    //vector<bool> visible(N + 1, true);
    int pom;
    for (int i = 1; i < N + 1; i++){
        cin >> pom >> coordinates[i].second;
        coordinates[i].first  = pom - XP;
    }

    sort(coordinates.begin() + 1, coordinates.end(), cmp);

    long long W;

    for (int i = 2; i < N + 1; i++){
        W = coordinates[i].first * coordinates[i - 1].second - coordinates[i - 1].first * coordinates[i].second;  
        if ( W == 0 ) ile--;
    }

    cout << ile << "\n";

}
