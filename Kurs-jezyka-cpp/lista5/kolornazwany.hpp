#ifndef KOLORNAZWANY_HPP
#define KOLORNAZWANY_HPP

#include "kolor.hpp"
#include <string>

class KolorNazwany : public virtual Kolor {
private:
    std::string nazwa;

public:
    KolorNazwany();

    KolorNazwany(unsigned short r, unsigned short g, unsigned short b, const std::string& n);

    std::string getNazwa() const;
    void setNazwa(const std::string& n);
};

#endif
