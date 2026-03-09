#ifndef MANIPULATORY_HPP
#define MANIPULATORY_HPP

#include "wejscie.hpp"
#include "wyjscie.hpp"

inline Wyjscie& klucz(Wyjscie& wyj, int k) {
    wyj.ustawKlucz(k);
    return wyj;
}

inline Wejscie& klucz(Wejscie& wej, int k) {
    wej.ustawKlucz(k);
    return wej;
}

#endif
