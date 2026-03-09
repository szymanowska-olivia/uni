#include "wszystkie_operatory.hpp"
#include <cmath>
#include <stdexcept>

namespace obliczenia {

Minus::Minus(Wyrazenie* o) : Operator1(o) {}

int Minus::oblicz() const {
    return -operand->oblicz();
}

std::string Minus::zapis() const {
    return "-(" + operand->zapis() + ")";
}

int Minus::priorytet() const {
    return 5;
}

Dodawanie::Dodawanie(Wyrazenie* l, Wyrazenie* p) : Operator2(l, p) {}

int Dodawanie::oblicz() const {
    return lewy->oblicz() + prawy->oblicz();
}

std::string Dodawanie::zapis() const {
    return nawias(lewy, false) + " + " + nawias(prawy, true);
}

int Dodawanie::priorytet() const {
    return 2;
}

Odejmowanie::Odejmowanie(Wyrazenie* l, Wyrazenie* p) : Operator2(l, p) {}

int Odejmowanie::oblicz() const {
    return lewy->oblicz() - prawy->oblicz();
}

std::string Odejmowanie::zapis() const {
    return nawias(lewy, false) + " - " + nawias(prawy, true);
}

int Odejmowanie::priorytet() const {
    return 2;
}

Mnozenie::Mnozenie(Wyrazenie* l, Wyrazenie* p) : Operator2(l, p) {}

int Mnozenie::oblicz() const {
    return lewy->oblicz() * prawy->oblicz();
}

std::string Mnozenie::zapis() const {
    return nawias(lewy, false) + " * " + nawias(prawy, true);
}

int Mnozenie::priorytet() const {
    return 3;
}

Dzielenie::Dzielenie(Wyrazenie* l, Wyrazenie* p) : Operator2(l, p) {}

int Dzielenie::oblicz() const {
    int dzielnik = prawy->oblicz();
    if (dzielnik == 0) throw std::runtime_error("Dzielenie przez zero!");
    return lewy->oblicz() / dzielnik;
}

std::string Dzielenie::zapis() const {
    return nawias(lewy, false) + " / " + nawias(prawy, true);
}

int Dzielenie::priorytet() const {
    return 3;
}

Potega::Potega(Wyrazenie* l, Wyrazenie* p) : Operator2(l, p) {}

int Potega::oblicz() const {
    return std::pow(lewy->oblicz(), prawy->oblicz());
}

std::string Potega::zapis() const {
    return nawias(lewy, false) + " ^ " + nawias(prawy, false);
}

int Potega::priorytet() const {
    return 4;
}

}
