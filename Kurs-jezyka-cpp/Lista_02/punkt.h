#ifndef PUNKT_H
#define PUNKT_H

class Punkt {
private:
    double x, y;

public:
    Punkt();  // Konstruktor bezargumentowy
    Punkt(double x, double y);  // Konstruktor z argumentami

    double getX() const;
    double getY() const;
    void translacja(double dx, double dy);  // Translacja z użyciem Wektora
    void symetriaOsiowa();  // Zadeklarowanie metody symetriaOsiowa

    void setX(double x);
    void setY(double y);
};

#endif // PUNKT_H
