#ifndef WYJATKI_HPP
#define WYJATKI_HPP

#include <stdexcept>
#include <string>

namespace obliczenia {

class wyjątek_wymierny : public std::logic_error {
public:
    explicit wyjątek_wymierny(const std::string& msg);
};

class dzielenie_przez_0 : public wyjątek_wymierny {
public:
    dzielenie_przez_0();
};

class przekroczenie_zakresu : public wyjątek_wymierny {
public:
    przekroczenie_zakresu();
};

} 

#endif
