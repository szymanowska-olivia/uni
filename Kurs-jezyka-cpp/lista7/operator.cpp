#include "operator.hpp"

Operator::Operator(Wyrazenie* l, Wyrazenie* p) : lewy(l), prawy(p) {}

Operator::~Operator() {
    delete lewy;
    delete prawy;
}

std::string Operator::nawias(Wyrazenie* wyrazenie, bool prawa_strona) const {
    bool dodaj_nawias = prawa_strona ? wyrazenie->priorytet() <= priorytet() : wyrazenie->priorytet() < priorytet();
    return dodaj_nawias ? "(" + wyrazenie->zapis() + ")" : wyrazenie->zapis();
}
