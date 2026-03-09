#ifndef KOLORTRANSPARENTNY_HPP
#define KOLORTRANSPARENTNY_HPP

#include "kolor.hpp"

class KolorTransparentny : public virtual Kolor {
private:
    unsigned short alpha;

public:
    KolorTransparentny();

    KolorTransparentny(unsigned short r, unsigned short g, unsigned short b, unsigned short a);

    unsigned short getAlpha() const;
    void setAlpha(unsigned short a);
};

#endif 
