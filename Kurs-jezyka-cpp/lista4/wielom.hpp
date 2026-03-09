#ifndef WIELOM_HPP
#define WIELOM_HPP

#include <initializer_list>
#include <stdexcept>
#include <iostream>

using namespace std;

class wielom {
private:
    int n;
    double *a; 

    friend istream& operator >> (istream &we, wielom &w);
    friend ostream& operator << (ostream &wy, const wielom &w);

public:
    wielom(int st = 0, double wsp = 1.0);
    wielom(int st, const double wsp[]);
    wielom(std::initializer_list<double> wsp);
    wielom(const wielom &w);
    wielom(wielom &&w);
    
    wielom& operator=(const wielom &w);
    wielom& operator=(wielom &&w);
    
    ~wielom();
    
    int stopien() const { return n; }

    double operator[](int i) const;
    double& operator[](int i);

    friend wielom operator + (const wielom &u, const wielom &v);
    friend wielom operator - (const wielom &u, const wielom &v);
    friend wielom operator * (const wielom &u, const wielom &v);
    friend wielom operator * (const wielom &v, double c);
    wielom& operator += (const wielom &v);
    wielom& operator -= (const wielom &v);
    wielom& operator *= (const wielom &v);
    wielom& operator *= (double c);
    double operator () (double x) const; 
};

#endif 