#include "kolor.hpp"

Kolor::Kolor(){
    this->red = 0;
    this->green = 0;
    this->blue = 0; 
}

Kolor::Kolor(unsigned short r, unsigned short g, unsigned short b) {
    if (r > 255||g> 255||b>255) 
        throw std::out_of_range("wartosc poza zakresem");
    this->red = r;
    this->green = g;
    this->blue = b;
}

unsigned short Kolor::getRed() const {
    return this->red;
}

unsigned short Kolor::getGreen() const {
    return this->green;
}

unsigned short Kolor::getBlue() const {
    return this->blue;
}

void Kolor::setRed(unsigned short r) {
    if (r > 255) 
        throw std::out_of_range("wartosc poza zakresem");
    this->red = r;
}

void Kolor::setGreen(unsigned short g) {
    if (g> 255) 
        throw std::out_of_range("wartosc poza zakresem");
    this->green = g;
}

void Kolor::setBlue(unsigned short b) {
    if (b>255) 
        throw std::out_of_range("wartosc poza zakresem");
    this->blue = b;
}

void Kolor::rozjasnij(unsigned short value) {
    this->red = (this->red + value > 255) ? 255 : this->red + value;
    this->green = (this->green + value > 255) ? 255 : this->green + value;
    this->blue = (this->blue + value > 255) ? 255 : this->blue + value;
}

void Kolor::przyciemnij(unsigned short value) {
    this->red = (this->red < value) ? 0 : this->red - value;
    this->green = (this->green < value) ? 0 : this->green - value;
    this->blue = (this->blue < value) ? 0 : this->blue - value;
}

Kolor Kolor::polacz(const Kolor& k1, const Kolor& k2) {
    return Kolor((k1.red + k2.red) / 2, (k1.green + k2.green) / 2, (k1.blue + k2.blue) / 2);
}
