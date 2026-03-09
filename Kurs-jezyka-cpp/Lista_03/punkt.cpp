#include "punkt.hpp"

punkt::punkt (){ x = y = 0; }
punkt::punkt(double x, double y) {
    this->x = x;  
    this->y = y;  
}

double punkt::getX () const { return x; }
double punkt::getY () const { return y; }

void punkt::setX(const double x_){ x = x_;}
void punkt::setY(const double y_){ y = y_;}