#ifndef PIKSELKOLOROWY_HPP
#define PIKSELKOLOROWY_HPP

#include "piksel.hpp"
#include "kolor.hpp"

class PikselKolorowy : public Piksel, private Kolor {
public:
    PikselKolorowy();
    PikselKolorowy(int x, int y, unsigned short r, unsigned short g, unsigned short b);

    void przesun(int dx, int dy);

    unsigned short getRed() const;
    unsigned short getGreen() const;
    unsigned short getBlue() const;

    void setRed(unsigned short r);
    void setGreen(unsigned short g);
    void setBlue(unsigned short b);
};

#endif
