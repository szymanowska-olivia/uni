#include "wyjscie.hpp"
#include <stdexcept>
#include <cctype>
#include <iostream>

Wyjscie::Wyjscie(const std::string& nazwa_pliku) : klucz(0) {
    plik.open(nazwa_pliku);
    plik.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    if (!plik.is_open())
        throw std::ios_base::failure("Nie mozna otworzyc pliku do zapisu.");
}

Wyjscie::~Wyjscie() {
    if (plik.is_open()) plik.close();
}

void Wyjscie::ustawKlucz(int k) {
    klucz = (k % 26 + 26) % 26;
}

std::string Wyjscie::szyfruj(const std::string& tekst) const {
    std::string wynik;
    for (char c : tekst) {
        if (std::isalpha(c)) {
            char baza = std::islower(c) ? 'a' : 'A';
            wynik += (c - baza + klucz) % 26 + baza;
        } else wynik += c;
    }
    return wynik;
}

void Wyjscie::pisz(const std::string& tekst) {
    std::string zaszyfrowany = szyfruj(tekst);
    //std::cout << "Szyfruje: '" << tekst << "' -> '" << zaszyfrowany << "'\n";
    plik << zaszyfrowany << '\n';
    if (plik.bad() || plik.fail()) throw std::ios_base::failure("Blad zapisu");
}


Wyjscie& operator<<(Wyjscie& w, const std::string& tekst) {
    w.pisz(tekst);
    return w;
}

