#include "piksel.hpp"
#include <stdexcept>
#include <cmath>

Piksel::Piksel() {
    this->setX(0);
    this->setY(0);
}

Piksel::Piksel(int x, int y) {
    this->setX(x);
    this->setY(y);
}

void Piksel::setX(int x) {
    if (x < 0 || x >= Piksel::SZEROKOSC_EKRANU) 
        throw std::out_of_range("poza zakresem ekranu");
    this->x = x;
}

void Piksel::setY(int y) {
    if (y < 0 || y >= Piksel::WYSOKOSC_EKRANU) 
        throw std::out_of_range("poza zakresem ekranu");
    this->y = y;
}

int Piksel::getX() const {
    return this->x;
}

int Piksel::getY() const {
    return this->y;
}

int Piksel::odlegloscOdLewej() const {
    return this->x;
}

int Piksel::odlegloscOdPrawej() const {
    return Piksel::SZEROKOSC_EKRANU - 1 - this->x;
}

int Piksel::odlegloscOdGory() const {
    return this->y;
}

int Piksel::odlegloscOdDolu() const {
    return Piksel::WYSOKOSC_EKRANU - 1 - this->y;
}

double Piksel::odleglosc(const Piksel& p1, const Piksel& p2) {
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

double Piksel::odleglosc(const Piksel* p1, const Piksel* p2) {
    if (p1 == nullptr || p2 == nullptr) 
        throw std::invalid_argument("pusty wskaznik");
    int dx = p1->x - p2->x;
    int dy = p1->y - p2->y;
    return std::sqrt(dx * dx + dy * dy);
}
