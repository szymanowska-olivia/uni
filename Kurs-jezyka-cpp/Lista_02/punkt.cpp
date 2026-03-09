#include "punkt.h"

Punkt::Punkt() : x(0), y(0) {}

Punkt::Punkt(double x, double y) : x(x), y(y) {}

double Punkt::getX() const {
    return x;
}

double Punkt::getY() const {
    return y;
}

void Punkt::translacja(double dx, double dy) {
    x += dx;
    y += dy;
}

void Punkt::symetriaOsiowa() {
    y = -y;  
}

void Punkt::setX(double x) {
    this->x = x;
}

void Punkt::setY(double y) {
    this->y = y;
}
