#include "pikselkolorowy.hpp"
#include <stdexcept>

PikselKolorowy::PikselKolorowy()
    : Piksel(), Kolor() {}

PikselKolorowy::PikselKolorowy(int x, int y, unsigned short r, unsigned short g, unsigned short b)
    : Piksel(x, y), Kolor(r, g, b) {}

void PikselKolorowy::przesun(int dx, int dy) {
    int nowyX = this->getX() + dx;
    int nowyY = this->getY() + dy;

    if (nowyX < 0 || nowyX >= Piksel::SZEROKOSC_EKRANU || nowyY < 0 || nowyY >= Piksel::WYSOKOSC_EKRANU)
        throw std::out_of_range("poza zakresem ekranu");
    this->setX(nowyX);
    this->setY(nowyY);
}

unsigned short PikselKolorowy::getRed() const {
    return Kolor::getRed();
}

unsigned short PikselKolorowy::getGreen() const {
    return Kolor::getGreen();
}

unsigned short PikselKolorowy::getBlue() const {
    return Kolor::getBlue();
}

void PikselKolorowy::setRed(unsigned short r) {
    Kolor::setRed(r);
}

void PikselKolorowy::setGreen(unsigned short g) {
    Kolor::setGreen(g);
}

void PikselKolorowy::setBlue(unsigned short b) {
    Kolor::setBlue(b);
}
