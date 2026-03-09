#include "wielom.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

wielom::wielom(int st, double wsp) {
    this->n = st;
    a = new double[this->n + 1];
    for (int i = 0; i < this->n; ++i) a[i] = 0.0;
    a[this->n] = wsp;
}

wielom::wielom(int st, const double wsp[]) {
    this->n = st;
    if (st < 0) throw std::invalid_argument("Ujemny stopien wielomianu");
    a = new double[this->n + 1];
    std::copy(wsp, wsp + this->n + 1, a);
}

wielom::wielom(std::initializer_list<double> wsp) {
    this->n = wsp.size()-1;
    a = new double[this->n + 1];
    std::copy(wsp.begin(), wsp.end(), a);
}

wielom::wielom(const wielom &w) {
    this->n = w.n;
    a = new double[this->n + 1];
    std::copy(w.a, w.a + this->n + 1, a);
}

wielom::wielom(wielom &&w) {
    this->n = w.n;
    this->a = w.a;
    w.a = nullptr;
    w.n = 0;
}

wielom& wielom::operator=(const wielom &w) {
    if (this != &w) {
        delete[] a;
        this->n = w.n;
        a = new double[this->n + 1];
        std::copy(w.a, w.a + this->n + 1, a);
    }
    return *this;
}

wielom& wielom::operator=(wielom &&w) {
    if (this != &w) {
        delete[] a;
        this->n = w.n;
        this->a = w.a;
        w.a = nullptr;
        w.n = 0;
    }
    return *this;
}

wielom::~wielom() { delete[] a; }

double wielom::operator[](int i) const {
    if (i < 0 || i > this->n) throw std::out_of_range("Indeks poza zakresem.");
    return a[i];
}

double& wielom::operator[](int i) {
    if (i < 0 || i > this->n) throw std::out_of_range("Indeks poza zakresem.");
    if (i == this->n && this->n != 0 && a[this->n] == 0) throw std::invalid_argument("Wspolczynnik przy najw potedze nie moze byc 0.");
    return a[i];
}

istream& operator >> (istream &we, wielom &w) {
    we >> w.n;
    delete[] w.a;  
    w.a = new double[w.n + 1];
    for (int i = 0; i <= w.n; ++i)
        we >> w.a[i];
    return we;
}

ostream& operator << (ostream &wy, const wielom &w) {
    bool first = true;  
    wy << w.stopien() << " stopień: ";  
    for (int i = w.n; i >= 0; i--) {
        double wyraz = w.a[i];
        if (wyraz == 0) continue;
        if (first) first = false;
        else {
            wy << (wyraz > 0 ? " + " : " - ");
            wyraz = abs(wyraz);  
        }

        if (i == 0) wy << wyraz; 
        else if (i == 1) wy << wyraz << "x";  
        else wy << wyraz << "x^" << i;  
    }

    if (first) wy << "0";  
    wy << endl;

    return wy;
}

wielom operator + (const wielom &u, const wielom &v) {
    int maxi = max(u.n,v.n);
    wielom w(maxi, 0.0);

    for (int i = 0; i <= maxi; i++) 
        w.a[i] = ((i <= u.n) ? u.a[i] : 0.0) + ((i <= v.n) ? v.a[i] : 0.0);

    return w;
}

wielom operator - (const wielom &u, const wielom &v) {
    int maxi = max(u.n,v.n);
    wielom w(maxi, 0.0);

    for (int i = 0; i <= maxi; i++) 
        w.a[i] = ((i <= u.n) ? u.a[i] : 0.0) - ((i <= v.n) ? v.a[i] : 0.0);

    return w;
}

wielom operator * (const wielom &u, const wielom &v) {
    int maxi = max(u.n,v.n);
    int mini = min(u.n,v.n);
    wielom w(u.n*v.n, 0.0);

    for (int i = 0; i <= maxi; i++) {
        for (int j = 0; j <= mini ; j++)
            w.a[i+j] = ((i <= u.n) ? u.a[i] : 0.0) * ((i <= v.n) ? v.a[i] : 0.0);
    }

    return w;
}

wielom operator * (const wielom &v, double c) {
    wielom w(v.n, 0.0);
    for (int i = 0; i <= v.n; i++)
        w.a[i] = w.a[i] * c;
    return w;
}

wielom& wielom::operator+=(const wielom &v) {
    *this = *this + v;
    return *this;
}

wielom& wielom::operator-=(const wielom &v) {
    *this = *this - v;
    return *this;
}

wielom& wielom::operator*=(const wielom &v) {
    *this = *this * v;
    return *this;
}

wielom& wielom::operator*=(double c) {
    for (int i = 0; i <= n; i++)
        a[i] *= c;
    return *this;
}

double wielom::operator()(double x) const {
    double wynik = a[n];
    for (int i = n - 1; i >= 0; i--)
        wynik = wynik * x + a[i];
    return wynik;
}


