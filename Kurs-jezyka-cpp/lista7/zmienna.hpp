#ifndef ZMIENNA_HPP
#define ZMIENNA_HPP

#include "wyrazenie.hpp"
#include <string>
#include <vector>
#include <utility>

class Zmienna : public Wyrazenie {
    std::string nazwa;
    static std::vector<std::pair<std::string, int>> zmienne;
public:
    Zmienna(std::string n);
    int oblicz() const override;
    std::string zapis() const override;
    int priorytet() const override;

    static void ustaw(std::string n, int wartosc);
    static void usun(std::string n);
    static bool istnieje(std::string n);
    static void wypisz();
};

#endif
