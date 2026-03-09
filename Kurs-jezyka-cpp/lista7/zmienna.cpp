#include "zmienna.hpp"
#include <iostream>
#include <algorithm>

std::vector<std::pair<std::string, int>> Zmienna::zmienne;

Zmienna::Zmienna(std::string n) : nazwa(n) {}

int Zmienna::oblicz() const {
    for (auto& zm : zmienne)
        if (zm.first == nazwa)
            return zm.second;
    throw std::runtime_error("Nieznana zmienna: " + nazwa);
}

std::string Zmienna::zapis() const {
    return nazwa;
}

int Zmienna::priorytet() const {
    return 100;
}

void Zmienna::ustaw(std::string n, int wartosc) {
    for (auto& zm : zmienne)
        if (zm.first == n) {
            zm.second = wartosc;
            return;
        }
    zmienne.push_back({n, wartosc});
}

void Zmienna::usun(std::string n) {
    zmienne.erase(std::remove_if(zmienne.begin(), zmienne.end(),
        [=](const std::pair<std::string, int>& zm) { return zm.first == n; }),
        zmienne.end());
}

bool Zmienna::istnieje(std::string n) {
    return std::any_of(zmienne.begin(), zmienne.end(),
        [=](const std::pair<std::string, int>& zm) { return zm.first == n; });
}

void Zmienna::wypisz() {
    std::cout << "Zmiennie:\n";
    for (auto& zm : zmienne)
        std::cout << zm.first << " = " << zm.second << std::endl;
}
