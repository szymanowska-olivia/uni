#include "liczba.hpp"
#include <string>

Liczba::Liczba(int w) {
    wartosc = w;
}

int Liczba::oblicz() const {
    return wartosc;
}

std::string Liczba::zapis() const {
    return std::to_string(wartosc);
}

int Liczba::priorytet() const {
    return 100;
}
