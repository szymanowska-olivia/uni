#ifndef WSZYSTKIE_OPERATORY_HPP
#define WSZYSTKIE_OPERATORY_HPP

#include "operator1.hpp"
#include "operator2.hpp"
#include <cmath>

namespace obliczenia {

class Minus : public Operator1 {
public:
    Minus(Wyrazenie* o);
    int oblicz() const override;
    std::string zapis() const override;
    int priorytet() const override;
};

class Dodawanie : public Operator2 {
public:
    Dodawanie(Wyrazenie* l, Wyrazenie* p);
    int oblicz() const override;
    std::string zapis() const override;
    int priorytet() const override;
};

class Odejmowanie : public Operator2 {
public:
    Odejmowanie(Wyrazenie* l, Wyrazenie* p);
    int oblicz() const override;
    std::string zapis() const override;
    int priorytet() const override;
};

class Mnozenie : public Operator2 {
public:
    Mnozenie(Wyrazenie* l, Wyrazenie* p);
    int oblicz() const override;
    std::string zapis() const override;
    int priorytet() const override;
};

class Dzielenie : public Operator2 {
public:
    Dzielenie(Wyrazenie* l, Wyrazenie* p);
    int oblicz() const override;
    std::string zapis() const override;
    int priorytet() const override;
};

class Potega : public Operator2 {
public:
    Potega(Wyrazenie* l, Wyrazenie* p);
    int oblicz() const override;
    std::string zapis() const override;
    int priorytet() const override;
};

}

#endif
