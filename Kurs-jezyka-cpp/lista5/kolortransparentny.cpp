#include "kolortransparentny.hpp"
#include <stdexcept>

KolorTransparentny::KolorTransparentny() {
    Kolor::setRed(0);
    Kolor::setGreen(0);
    Kolor::setBlue(0);
    this->alpha = 0;
}

KolorTransparentny::KolorTransparentny(unsigned short r, unsigned short g, unsigned short b, unsigned short a) {
    if (r > 255 || g > 255 || b > 255 || a > 255) 
        throw std::out_of_range("wartosc poza zakresem");

    this->setRed(r);
    this->setGreen(g);
    this->setBlue(b);
    this->alpha = a;
}

unsigned short KolorTransparentny::getAlpha() const {
    return this->alpha;
}

void KolorTransparentny::setAlpha(unsigned short a) {
    if (a > 255) 
        throw std::out_of_range("wartosc poza zakresem");
    this->alpha = a;
}
