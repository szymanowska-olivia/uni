#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const double PI = 3.14159265358979323846;
const double G = 4 * (PI * PI);
const double h = 1e-3;
const int N = 1000;

// Struktura dla ciała
struct Body {
    double m;
    pair<double,double> r;
    pair<double,double> v;
};

// v_{n+1} = a_n * h + v_n 
pair<double,double> Velocity_Euler(pair<double,double> v, pair<double,double> a) {
    return {v.first + a.first * h, v.second + a.second * h};
}

// r_{n+1} = v_n * h + r_n
pair<double,double> Position_Euler(pair<double,double> r, pair<double,double> v) {
    return {r.first + v.first * h, r.second + v.second * h};
}

// v_{n+1} = v_{n-1} + 2*h*a_n
pair<double,double> Velocity_Verlet(pair<double,double> v_prev, pair<double,double> a) {
    return {v_prev.first + 2*h*a.first, v_prev.second + 2*h*a.second};
}


// r_{n+1} = r_{n-1} + 2*h*v_n
pair<double,double> Position_Verlet(pair<double,double> r_prev, pair<double,double> v) {
    return {r_prev.first + 2*h*v.first, r_prev.second + 2*h*v.second};
}

// Przyspieszenie dla kilku ciał
vector<pair<double,double>> AccelerationN(const vector<Body>& bodies) {
    int n = bodies.size();
    vector<pair<double,double>> a(n, {0,0});
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) continue;
            double dx = bodies[j].r.first - bodies[i].r.first;
            double dy = bodies[j].r.second - bodies[i].r.second;
            double dist = sqrt(dx*dx + dy*dy);
            double f = G / pow(dist,3);
            a[i].first += dx * bodies[j].m * f;
            a[i].second += dy * bodies[j].m * f;
        }
    }
    return a;
}

//metoda z pierwszego wzoru na pochodną
void Euler_method(vector<Body> bodies) {
    cout << "Euler_method\n";
    for(int step=0;step<N;step++){
        auto a = AccelerationN(bodies);
        for(int i=0;i<bodies.size();i++){
            bodies[i].v = Velocity_Euler(bodies[i].v, a[i]);
            bodies[i].r = Position_Euler(bodies[i].r, bodies[i].v);
        }

        if (step == N-1){
            cout << "Krok " << step << ":\n";
            for(int i=0;i<bodies.size();i++)
                cout << "  Cialo " << i << ": (" << bodies[i].r.first << ", " << bodies[i].r.second << ")\n";

        }
    }
}

//metoda z drugiego wzoru na pochodną
void Verlet_method(vector<Body> bodies) {
    cout << "Verlet_method\n";

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

    cout << "Krok 0:\n";
    for(int i=0;i<bodies.size();i++)
        cout << "  Cialo " << i << ": (" << r_prev[i].r.first << ", " << r_prev[i].r.second << ")\n";
    cout << "Krok 1:\n";
    for(int i=0;i<bodies.size();i++)
        cout << "  Cialo " << i << ": (" << r_curr[i].r.first << ", " << r_curr[i].r.second << ")\n";

    for(int step=2;step<N;step++){
        auto a_curr = AccelerationN(r_curr);
        vector<Body> r_next = r_curr;
        vector<Body> v_next = v_curr;
        for(int i=0;i<bodies.size();i++){
            r_next[i].r = Position_Verlet(r_prev[i].r, v_curr[i].v);
            v_next[i].v = Velocity_Verlet(v_prev[i].v, a_curr[i]);
        }

        if(step == N-1){
            cout << "Krok " << step << ":\n";
            for(int i=0;i<bodies.size();i++)
                cout << "  Cialo " << i << ": (" << r_next[i].r.first << ", " << r_next[i].r.second << ")\n";

        }

        r_prev = r_curr;
        r_curr = r_next;
        v_prev = v_curr;
        v_curr = v_next;
    }
}

int main() {
    vector<vector<Body>> examples = {
        // 1) Słońce-Ziemia-Księżyc
        {
            {1.0, {0,0}, {0, -3.003e-6/1.0*2*PI}}, //wartośći początkowe dla Słońca       
            {3.003e-6, {1.0,0}, {0, 2*PI}}, //dla Ziemi              
            {3.694e-8, {1.0+0.00257,0}, {0, 2*PI+0.00257*84}} //dla Księżyca
        },
        // 2) Podwójna gwiazda + planeta
        {
            {1.0, {-0.1,0}, {0, 2*PI*0.2/0.2}},   // gwiazda A
            {1.0, {0.1,0}, {0, -2*PI*0.2/0.2}},   // gwiazda B
            {3e-6, {1.0,0}, {0, 2*PI}}           // planeta
        },
        // 3) Słońce + Jowisz + statek kosmiczny
        {
            {1.0, {0,0}, {0,0}},                     // Sun
            {9.545e-4, {5.2,0}, {0, 2*PI/5.2}},      // Jupiter
            {1e-12, {1.0,-0.05}, {0, 2*PI+0.05}}    // craft
        }
    };

    for(int i=0;i<examples.size();i++){
        cout << "\n==== Przypadek " << i+1 << " ====\n";
        Euler_method(examples[i]);
        cout << endl;
        Verlet_method(examples[i]);
    }
}
