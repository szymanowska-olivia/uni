#include "kolejka.hpp"
#include "punkt.hpp"
#include <initializer_list>
#include <stdexcept>
#include <iostream> 

kolejka::kolejka(int pojemnosc) {
    this->pojemnosc = pojemnosc;
    this->pocz = 0;
    this->ile = 0;
    tab = new punkt[pojemnosc];
}

kolejka::kolejka() : kolejka(1) {}

kolejka::kolejka(std::initializer_list<punkt> lista) {
    pojemnosc = lista.size();
    pocz = 0;
    ile = lista.size();
    tab = new punkt[pojemnosc];

    int i = 0;
    for (auto it = lista.begin(); it != lista.end(); it++) 
        tab[i++] = *it;
}

kolejka::kolejka(const kolejka& other) {
    pojemnosc = other.pojemnosc;
    pocz = other.pocz;
    ile = other.ile;
    tab = new punkt[pojemnosc];

    for (int i = 0; i < ile; i++) 
        tab[i] = other.tab[(other.pocz + i) % pojemnosc];
}

kolejka::kolejka(kolejka&& other) {
    pojemnosc = other.pojemnosc;
    pocz = other.pocz;
    ile = other.ile;
    tab = other.tab;

    other.tab = nullptr;
    other.pojemnosc = 0;
    other.pocz = 0;
    other.ile = 0;
}

kolejka& kolejka::operator=(const kolejka& other) {
    if (this == &other) return *this;
    delete[] tab;
    pojemnosc = other.pojemnosc;
    pocz = other.pocz;
    ile = other.ile;
    tab = new punkt[pojemnosc];
    for (int i = 0; i < ile; i++) tab[i] = other.tab[(other.pocz + i) % pojemnosc];
    return *this;
}

kolejka& kolejka::operator=(kolejka&& other) {
    if (this == &other) return *this;
    delete[] tab;
    pojemnosc = other.pojemnosc;
    pocz = other.pocz;
    ile = other.ile;
    tab = other.tab;
    other.tab = nullptr;
    other.pojemnosc = 0;
    other.pocz = 0;
    other.ile = 0;
    return *this;
}

kolejka::~kolejka() {
    delete[] tab;
}
void kolejka::wstaw(punkt p) {
    if (ile == pojemnosc) {
        std::cerr << "Błąd: Kolejka jest pełna" << std::endl;  
        return;
    }
    tab[(pocz + ile) % pojemnosc] = p;
    ile++;
}

punkt kolejka::usun() {
    if (ile == 0) {
        std::cerr << "Błąd: Kolejka jest pusta" << std::endl;  
        return punkt();  
    }
    punkt result = tab[pocz];
    pocz = (pocz + 1) % pojemnosc;
    ile--;
    return result;
}

punkt kolejka::zprzodu() {
    if (ile == 0) {
        std::cerr << "Błąd: Kolejka jest pusta" << std::endl; 
        return punkt();  
    }
    return tab[pocz];
}


int kolejka::dlugosc() {
    return ile;
}
