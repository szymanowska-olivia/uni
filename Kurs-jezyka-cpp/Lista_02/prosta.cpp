#include "prosta.h"

Prosta::Prosta(double A, double B, double C) : A(A), B(B), C(C) {}

double Prosta::getA() const {
    return A;
}

double Prosta::getB() const {
    return B;
}

double Prosta::getC() const {
    return C;
}
