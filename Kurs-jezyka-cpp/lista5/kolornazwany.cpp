#include "kolornazwany.hpp"
#include <stdexcept>
#include <cctype>

KolorNazwany::KolorNazwany() {
    this->setRed(0);
    this->setGreen(0);
    this->setBlue(0);
    this->nazwa = "";
}

KolorNazwany::KolorNazwany(unsigned short r, unsigned short g, unsigned short b, const std::string& n) {
    if (r > 255 || g > 255 || b > 255) 
        throw std::out_of_range("wartosc poza zakresem");
    this->setRed(r);
    this->setGreen(g);
    this->setBlue(b);
    this->setNazwa(n); 
}

std::string KolorNazwany::getNazwa() const {
    return this->nazwa;
}

void KolorNazwany::setNazwa(const std::string& n) {
    for (char c : n) {
        if (c < 'a' || c > 'z') {
            throw std::invalid_argument("dozwolone sa tylko male litery alfabetu");
            break;
        }
    }
    this->nazwa = n;
}
