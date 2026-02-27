/*
Dane jest N punktów na płaszczyźnie. Twoim zadaniem jest znaleźć ich otoczkę wypukłą.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

vector<pair<long long, long long>> coordinates;
vector<pair<long long, long long>> convex;


long long W_calc(pair<long long, long long> xy1, pair<long long, long long> xy2, pair<long long, long long> XP){
    //cout << xy1.first - XP.first<< " * " <<xy2.second - XP.second << " - " << xy2.first - XP.first << " * " << xy1.second - XP.second << " \n";

    return  ((xy1.first - XP.first) * (xy2.second - XP.second)) - ((xy2.first - XP.first) * (xy1.second - XP.second));
}

void convex_hull (int N){
    long long W;

    convex.push_back({coordinates[1].first, coordinates[1].second});
    for (int i = 2; i < N + 1; i++){
       // if (i == N + 1) idx = 1;
        

        while (convex.size() > 1) {
           // cout << convex[convex.size() - 1].first << " "<< convex[convex.size() - 1].second<< "c " << convex[convex.size() - 2].first << " "<< convex[convex.size() - 2].second<< "c " << coordinates[i].first << " "<< coordinates[idx].second << "\n";
            W = W_calc(convex[convex.size() - 2], convex[convex.size() - 1], coordinates[i]);
           // cout << "W " << W << "\n";
            if (W >= 0) break;
            convex.pop_back();
        }       

        convex.push_back({coordinates[i].first, coordinates[i].second});
    }

    reverse(coordinates.begin() + 1, coordinates.end());

    convex.push_back({coordinates[1].first, coordinates[1].second});
    for (int i = 2; i < N + 1; i++){
       // if (i == N + 1) idx = 1;
        

        while (convex.size() > 1) {
           // cout << convex[convex.size() - 1].first << " "<< convex[convex.size() - 1].second<< "c " << convex[convex.size() - 2].first << " "<< convex[convex.size() - 2].second<< "c " << coordinates[i].first << " "<< coordinates[idx].second << "\n";
            W = W_calc(convex[convex.size() - 2], convex[convex.size() - 1], coordinates[i]);
           // cout << "W " << W << "\n";
            if (W >= 0) break;
            convex.pop_back();
        }       

        convex.push_back({coordinates[i].first, coordinates[i].second});
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);   

    int N;
    cin >> N;

    coordinates.resize(N + 1);


    for (int i = 1; i < N + 1; i++) cin >> coordinates[i].first >> coordinates[i].second;

    sort(coordinates.begin() + 1, coordinates.end());

    coordinates[0].first = coordinates[1].first, coordinates[0].second = coordinates[1].second;

    for (int i = 1; i < N + 1; i++){
        coordinates[i].first -= coordinates[0].first;
        coordinates[i].second -= coordinates[0].second;
    } 
    //for (int i = 1; i < coordinates.size(); i++) cout << coordinates[i].first << " " << coordinates[i].second << "\n";

    convex_hull(N);

    sort(convex.begin(), convex.end());
    cout << convex.size() - 2  << "\n";
    for (int i = 1; i < convex.size() - 1; i++) cout << convex[i].first + coordinates[0].first<< " " << convex[i].second + coordinates[0].second<< "\n";
}
