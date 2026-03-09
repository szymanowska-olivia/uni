#include "kolortransnaz.hpp"
#include <stdexcept>

KolorTransNaz::KolorTransNaz() {
    Kolor::setRed(0);
    Kolor::setGreen(0);
    Kolor::setBlue(0);
    this->setAlpha(0);
    this->setNazwa("");
}

KolorTransNaz::KolorTransNaz(unsigned short r, unsigned short g, unsigned short b, unsigned short a, const std::string& n) {
    if (r > 255 || g > 255 || b > 255 || a > 255) 
        throw std::out_of_range("wartosc poza zakresem");

    Kolor::setRed(r);
    Kolor::setGreen(g);
    Kolor::setBlue(b);
    this->setAlpha(a);
    this->setNazwa(n);
}
