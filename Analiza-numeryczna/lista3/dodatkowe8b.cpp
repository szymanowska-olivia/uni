#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159265358979323846;
const double G = 4 * (PI * PI);

// początkowe wartości dla przykładu ciało 1 - Słońce, ciało 2 - Ziemia
const double m1 = 1.0, m2 = 3e-6; // masy ciał
const pair<double, double> r1_0 = {0, 0}, r2_0 = {1, 0}; // położenie ciał (Ziemia 1 AU od Słońca)
const pair<double, double> v1_0 = {0, 0}, v2_0 = {0, 2 * PI}; // prędkość orbitalna

const double h = 0.01; // krok czasowy (np. 0.01 roku)
const int N = 5;       // liczba kroków 

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

// Przyspieszenie grawitacyjne ciała 1 i ciała 2
pair<pair<double,double>, pair<double,double>> Acceleration(pair<double,double> r1, pair<double,double> r2) {
    double dx = r2.first - r1.first, dy = r2.second - r1.second;
    double dist = sqrt(dx*dx + dy*dy);
    double fact = G / pow(dist,3);

    pair<double,double> a1 = {dx * fact * m2, dy * fact * m2};
    pair<double,double> a2 = {-dx * fact * m1, -dy * fact * m1};

    return {a1, a2};
}

//metoda z pierwszego wzoru na pochodną
void Euler_method() {

    pair<double,double> r1 = r1_0, r2 = r2_0, v1 = v1_0, v2 = v2_0;

    cout << "Euler_method" << endl;

    for (int i = 0; i < N; i++) {
        auto a = Acceleration(r1, r2);
        pair<double,double> a1 = a.first, a2 = a.second;

        v1 = Velocity_Euler(v1, a1);
        v2 = Velocity_Euler(v2, a2);
        r1 = Position_Euler(r1, v1);
        r2 = Position_Euler(r2, v2);

        cout << "Krok " << i << ": r1 = (" << r1.first << ", " << r1.second << "), r2 = (" << r2.first << ", " << r2.second << ")\n";
    }
}


//metoda z drugiego wzoru na pochodną
void Verlet_method() {

    pair<double,double> r1_prev = r1_0, r2_prev = r2_0, v1_prev = v1_0, v2_prev = v2_0;

    cout << "Verlet_method" << endl;

    auto a0 = Acceleration(r1_prev, r2_prev);
    // dla n = 1 liczymy eulerem 
    pair<double,double> r1_curr = { r1_prev.first + h * v1_prev.first, r1_prev.second + h * v1_prev.second }, 
                        r2_curr = { r2_prev.first + h * v2_prev.first, r2_prev.second + h * v2_prev.second }, 
                        v1_curr = { v1_prev.first + h * a0.first.first, v1_prev.second + h * a0.first.second }, 
                        v2_curr = { v2_prev.first + h * a0.second.first, v2_prev.second + h * a0.second.second };

    cout << "Krok 0: r1 = (" << r1_prev.first << ", " << r1_prev.second << "), r2 = (" << r2_prev.first << ", " << r2_prev.second << ")\n";
    cout << "Krok 1: r1 = (" << r1_curr.first << ", " << r1_curr.second << "), r2 = (" << r2_curr.first << ", " << r2_curr.second << ")\n";

    for(int i = 2; i < N; i++) {

        auto a_curr = Acceleration(r1_curr, r2_curr);
        pair<double,double> a1 = a_curr.first, a2 = a_curr.second;
        pair<double,double> r1_next = Position_Verlet(r1_prev, v1_curr), r2_next = Position_Verlet(r2_prev, v2_curr);
        pair<double,double> v1_next = Velocity_Verlet(v1_prev, a1), v2_next = Velocity_Verlet(v2_prev, a2);

        cout << "Krok " << i << ": r1 = (" << r1_next.first << ", " << r1_next.second << "), r2 = (" << r2_next.first << ", " << r2_next.second << ")\n";

        r1_prev = r1_curr; 
        r1_curr = r1_next;
        r2_prev = r2_curr; 
        r2_curr = r2_next;
        v1_prev = v1_curr; 
        v1_curr = v1_next;
        v2_prev = v2_curr; 
        v2_curr = v2_next;
    }
}


int main() {
    Euler_method();
    cout << endl;
    Verlet_method();
}
