#ifndef PROSTA_H
#define PROSTA_H

class Prosta {
private:
    double A, B, C;

public:
    Prosta(double A, double B, double C);
    double getA() const;
    double getB() const;
    double getC() const;
};

#endif
