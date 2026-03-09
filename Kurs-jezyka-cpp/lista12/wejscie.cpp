#include "wejscie.hpp"
#include <stdexcept>
#include <cctype>

Wejscie::Wejscie(const std::string& nazwa_pliku) : klucz(0) {
    plik.open(nazwa_pliku);
    plik.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    if (!plik.is_open())
        throw std::ios_base::failure("Nie mozna otworzyc pliku do odczytu.");
}

Wejscie::~Wejscie() {
    if (plik.is_open()) plik.close();
}

void Wejscie::ustawKlucz(int k) {
    klucz = (k % 26 + 26) % 26;
}

std::string Wejscie::deszyfruj(const std::string& tekst) const {
    std::string wynik;
    for (char c : tekst) {
        if (std::isalpha(c)) {
            char baza = std::islower(c) ? 'a' : 'A';
            wynik += (c - baza - klucz + 26) % 26 + baza;
        } else wynik += c;
    }
    return wynik;
}

std::string Wejscie::czytaj() {
    std::string linia;
    std::getline(plik, linia);
    return deszyfruj(linia);
}

Wejscie& operator>>(Wejscie& w, std::string& linia) {
    linia = w.czytaj();
    return w;
}
