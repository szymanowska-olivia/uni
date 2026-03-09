#ifndef STALA_HPP
#define STALA_HPP

#include "wyrazenie.hpp"
#include <string>

class Stala : public Wyrazenie {
protected:
    std::string nazwa;
    int wartosc;
public:
    Stala(std::string n, int w);
    int oblicz() const override;
    std::string zapis() const override;
    int priorytet() const override;
};

class Zero : public Stala {
public:
    Zero();
};

class Jeden : public Stala {
public:
    Jeden();
};

#endif
