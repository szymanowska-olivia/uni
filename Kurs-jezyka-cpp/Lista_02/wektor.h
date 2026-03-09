#ifndef WEKTOR_H
#define WEKTOR_H

class Wektor {
private:
    double dx, dy;

public:
    Wektor(double dx = 0, double dy = 0);
    double getDx() const;
    double getDy() const;
    void setDx(double dx);
    void setDy(double dy);
};

#endif
