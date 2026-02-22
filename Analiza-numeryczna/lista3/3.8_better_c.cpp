#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

const double PI = 3.14159265358979323846;
const double G = 4 * (PI * PI);
const double h = 5e-6;   // mniejszy krok dla stabilniejszej symulacji
const int N = 1000000;    // liczba kroków symulacji

struct Body {
    double m;
    pair<double,double> r;
    pair<double,double> v;
};

// Euler
pair<double,double> Velocity_Euler(pair<double,double> v, pair<double,double> a) {
    return {v.first + a.first * h, v.second + a.second * h};
}
pair<double,double> Position_Euler(pair<double,double> r, pair<double,double> v) {
    return {r.first + v.first * h, r.second + v.second * h};
}

// Velocity Verlet
pair<double,double> Position_Verlet(pair<double,double> r, pair<double,double> v, pair<double,double> a) {
    return {r.first + v.first*h + 0.5*a.first*h*h,
            r.second + v.second*h + 0.5*a.second*h*h};
}

pair<double,double> Velocity_Verlet(pair<double,double> v, pair<double,double> a_old, pair<double,double> a_new) {
    return {v.first + 0.5*(a_old.first + a_new.first)*h,
            v.second + 0.5*(a_old.second + a_new.second)*h};
}

// Przyspieszenie z softeningiem
vector<pair<double,double>> AccelerationN(const vector<Body>& bodies) {
    int n = bodies.size();
    vector<pair<double,double>> a(n, {0,0});
    double eps = 1e-5;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) continue;
            double dx = bodies[j].r.first - bodies[i].r.first;
            double dy = bodies[j].r.second - bodies[i].r.second;
            double dist = sqrt(dx*dx + dy*dy + eps*eps);
            double f = G / pow(dist,3);
            a[i].first += dx * bodies[j].m * f;
            a[i].second += dy * bodies[j].m * f;
        }
    }
    return a;
}

// Euler
void Euler_method(vector<Body> bodies, int case_num) {
    cout << "Euler_method\n";

    ofstream file("euler_case" + to_string(case_num) + ".csv");
    file << "step";
    for(int i=0;i<bodies.size();i++)
        file << ",x" << i << ",y" << i;
    file << "\n";

    for(int step=0;step<N;step++){
        auto a = AccelerationN(bodies);
        vector<pair<double,double>> new_positions(bodies.size());
        vector<pair<double,double>> new_velocities(bodies.size());

        for(int i=0;i<bodies.size();i++){
            new_velocities[i] = Velocity_Euler(bodies[i].v, a[i]);
            new_positions[i] = Position_Euler(bodies[i].r, bodies[i].v);
        }

        for(int i=0;i<bodies.size();i++){
            bodies[i].v = new_velocities[i];
            bodies[i].r = new_positions[i];
        }

        file << step;
        for(int i=0;i<bodies.size();i++)
            file << "," << bodies[i].r.first << "," << bodies[i].r.second;
        file << "\n";
    }
    file.close();

    cout << "Zapisano dane do pliku: euler_case" << case_num << ".csv\n";
}

// Velocity Verlet
void Verlet_method(vector<Body> bodies, int case_num) {
    cout << "Verlet_method\n";

    ofstream file("verlet_case" + to_string(case_num) + ".csv");
    file << "step";
    for(int i=0;i<bodies.size();i++)
        file << ",x" << i << ",y" << i;
    file << "\n";

    auto a_curr = AccelerationN(bodies);

    for(int step=0; step<N; step++){
        // oblicz nowe pozycje
        vector<pair<double,double>> r_next(bodies.size());
        for(int i=0;i<bodies.size();i++){
            r_next[i] = Position_Verlet(bodies[i].r, bodies[i].v, a_curr[i]);
        }

        // tymczasowo aktualizujemy pozycje w strukturze, żeby policzyć nowe przyspieszenia
        vector<Body> bodies_temp = bodies;
        for(int i=0;i<bodies.size();i++){
            bodies_temp[i].r = r_next[i];
        }

        auto a_next = AccelerationN(bodies_temp);

        // oblicz nowe prędkości
        for(int i=0;i<bodies.size();i++){
            bodies[i].v = Velocity_Verlet(bodies[i].v, a_curr[i], a_next[i]);
            bodies[i].r = r_next[i];
        }

        a_curr = a_next;

        // zapis do pliku
        file << step;
        for(int i=0;i<bodies.size();i++)
            file << "," << bodies[i].r.first << "," << bodies[i].r.second;
        file << "\n";
    }

    file.close();
    cout << "Zapisano dane do pliku: verlet_case" << case_num << ".csv\n";
}

int main() {
    vector<vector<Body>> examples = {
        // 1) Słońce-Ziemia-Księżyc
        {
            {1.0, {0,0}, {0, -3.003e-6/1.0*2*PI}},      
            {3.003e-6, {1.0,0}, {0, 2*PI}},              
            {3.694e-8, {1.0+0.00257,0}, {0, 2*PI + sqrt(G * 3.003e-6 / 0.00257)}} 
        },
        // 2) Podwójna gwiazda + planeta
        {
            {1.0, {-0.1,0}, {0, 2*PI*0.2/0.2}},
            {1.0, {0.1,0}, {0, -2*PI*0.2/0.2}},
            {3e-6, {1.0,0}, {0, 2*PI}}
        },
        // 3) Słońce + Jowisz + statek
        {
            {1.0, {0,0}, {0,0}},
            {9.545e-4, {5.2,0}, {0, 2*PI/5.2}},
            {1e-12, {1.0,-0.05}, {0, 2*PI+0.05}}
        }
    };

    for(int i=0;i<examples.size();i++){
        cout << "\n==== Przypadek " << i+1 << " ====\n";
        Euler_method(examples[i], i+1);
        Verlet_method(examples[i], i+1);
    }
}
