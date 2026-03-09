#ifndef KOLOR_HPP
#define KOLOR_HPP

#include <stdexcept>

class Kolor {
private:
    unsigned short red, green, blue;
public:
    Kolor();
    Kolor(unsigned short r, unsigned short g, unsigned short b);

    unsigned short getRed() const;
    unsigned short getGreen() const;
    unsigned short getBlue() const;

    void setRed(unsigned short r);
    void setGreen(unsigned short g);
    void setBlue(unsigned short b);

    void rozjasnij(unsigned short value);
    void przyciemnij(unsigned short value);

    static Kolor polacz(const Kolor& k1, const Kolor& k2);
};

#endif 