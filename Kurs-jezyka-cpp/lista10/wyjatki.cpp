#include "wyjatki.hpp"

namespace obliczenia {

wyjątek_wymierny::wyjątek_wymierny(const std::string& msg)
    : std::logic_error(msg) {}

dzielenie_przez_0::dzielenie_przez_0()
    : wyjątek_wymierny("Dzielenie przez zero!") {}

przekroczenie_zakresu::przekroczenie_zakresu()
    : wyjątek_wymierny("Przekroczenie zakresu typu int!") {}

} 
