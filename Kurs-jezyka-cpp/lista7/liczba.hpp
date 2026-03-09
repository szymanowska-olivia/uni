#ifndef LICZBA_HPP
#define LICZBA_HPP

#include "wyrazenie.hpp"

class Liczba : public Wyrazenie {
    int wartosc;
public:
    Liczba(int w);
    int oblicz() const override;
    std::string zapis() const override;
    int priorytet() const override;
};

#endif
