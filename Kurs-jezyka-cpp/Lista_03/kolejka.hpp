#ifndef KOLEJKA_HPP
#define KOLEJKA_HPP
#include "punkt.hpp"
#include <initializer_list>

class kolejka{

private:

    int pojemnosc, pocz, ile;
    punkt *tab;

public:

    kolejka (int pojemnosc);
    kolejka ();
    kolejka (std::initializer_list<punkt> lista);
    kolejka (const kolejka& other);
    kolejka(kolejka&& other);

    kolejka& operator=(const kolejka& other);
    kolejka& operator=(kolejka&& other);

    ~kolejka();

    void wstaw(punkt p);
    punkt usun();
    punkt zprzodu();
    int dlugosc();
};

#endif