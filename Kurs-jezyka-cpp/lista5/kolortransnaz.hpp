#ifndef KOLORTRANSNAZ_HPP
#define KOLORTRANSNAZ_HPP

#include "kolortransparentny.hpp"
#include "kolornazwany.hpp"

class KolorTransNaz : public KolorTransparentny, public KolorNazwany {
public:
    KolorTransNaz();

    KolorTransNaz(unsigned short r, unsigned short g, unsigned short b, unsigned short a, const std::string& n);
};

#endif 
