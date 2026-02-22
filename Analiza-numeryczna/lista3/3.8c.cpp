#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

const double PI = 3.14159265358979323846;
const double G = 4 * (PI * PI);
const double h = 1e-5;   // mniejszy krok dla stabilniejszej symulacji
const int N = 1000000;     // liczba kroków symulacji

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

// Verlet 
pair<double,double> Velocity_Verlet(pair<double,double> v_prev, pair<double,double> a) {
    return {v_prev.first + 2*h*a.first, v_prev.second + 2*h*a.second};
}
pair<double,double> Position_Verlet(pair<double,double> r_prev, pair<double,double> v) {
    return {r_prev.first + 2*h*v.first, r_prev.second + 2*h*v.second};
}

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
            new_positions[i] = Position_Euler(bodies[i].r, bodies[i].v); // używamy starej v
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

// Verlet
void Verlet_method(vector<Body> bodies, int case_num) {
    cout << "Verlet_method\n";

    ofstream file("verlet_case" + to_string(case_num) + ".csv");
    file << "step";
    for(int i=0;i<bodies.size();i++)
        file << ",x" << i << ",y" << i;
    file << "\n";

    vector<Body> r_prev = bodies;
    vector<Body> v_prev = bodies;

    auto a0 = AccelerationN(r_prev);
    vector<Body> r_curr = r_prev;
    vector<Body> v_curr = v_prev;

    // krok 1 Eulerem
    for(int i=0;i<bodies.size();i++){
        r_curr[i].r = Position_Euler(r_prev[i].r, v_prev[i].v);
        v_curr[i].v = Velocity_Euler(v_prev[i].v, a0[i]);
        r_curr[i].m = r_prev[i].m;
        v_curr[i].m = r_prev[i].m;
    }

    for(int step=0;step<N;step++){
        if(step == 0) {
            file << step;
            for(int i=0;i<bodies.size();i++)
                file << "," << r_prev[i].r.first << "," << r_prev[i].r.second;
            file << "\n";
        }
        else if(step == 1) {
            file << step;
            for(int i=0;i<bodies.size();i++)
                file << "," << r_curr[i].r.first << "," << r_curr[i].r.second;
            file << "\n";
        }
        else {
            auto a_curr = AccelerationN(r_curr);
            vector<Body> r_next = r_curr;
            vector<Body> v_next = v_curr;
            for(int i=0;i<bodies.size();i++){
                r_next[i].r = Position_Verlet(r_prev[i].r, v_curr[i].v);
                v_next[i].v = Velocity_Verlet(v_prev[i].v, a_curr[i]);
            }

            file << step;
            for(int i=0;i<bodies.size();i++)
                file << "," << r_next[i].r.first << "," << r_next[i].r.second;
            file << "\n";

            r_prev = r_curr;
            r_curr = r_next;
            v_prev = v_curr;
            v_curr = v_next;
        }
    }
    file.close();
    cout << "Zapisano dane do pliku: verlet_case" << case_num << ".csv\n";
}

int main() {

    vector<vector<Body>> examples = {
        {
            {1.0, {0.0, 0.0}, {0.0, 0.0}},                                   // Słońce
            {3.003e-6, {1.0, 0.0}, {0.0, 2*PI - 3.694e-8 / 3.003e-6 * 0.00257 * 2*PI}}, // Ziemia 
            {3.694e-8, {1.0 + 0.00257, 0.0}, {0.0, 2*PI + sqrt(G * 3.003e-6 / 0.00257)}} // Księżyc
        },
        {
            {1.0, {-0.1,0}, {0, 2*PI*0.2/0.2}},
            {1.0, {0.1,0}, {0, -2*PI*0.2/0.2}},
            {3e-6, {1.0,0}, {0, 2*PI}}
        },
        {
            {1.0, {0,0}, {0,0}},                  // Słońce
            {9.545e-4, {5.2, 0.0}, {0, 2*PI/5.2}}, // Jowisz – w płaszczyźnie statku
            {1e-12, {1.0, 0.0}, {0, 9}}         // statek – start z orbity Ziemi
        }   
    };

    for(int i=0;i<examples.size();i++){
        cout << "\n==== Przypadek " << i+1 << " ====\n";
        Euler_method(examples[i], i+1);
        Verlet_method(examples[i], i+1);
    }
}
