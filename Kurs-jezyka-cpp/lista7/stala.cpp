#include "stala.hpp"

Stala::Stala(std::string n, int w) : nazwa(n), wartosc(w) {}

int Stala::oblicz() const {
    return wartosc;
}

std::string Stala::zapis() const {
    return nazwa;
}

int Stala::priorytet() const {
    return 100;
}

Zero::Zero() : Stala("0", 0) {}
Jeden::Jeden() : Stala("1", 1) {}
