#include "wektor.h"

Wektor::Wektor(double dx, double dy) : dx(dx), dy(dy) {}

double Wektor::getDx() const {
    return dx;
}

double Wektor::getDy() const {
    return dy;
}

void Wektor::setDx(double dx) {
    this->dx = dx;
}

void Wektor::setDy(double dy) {
    this->dy = dy;
}
