#ifndef WYMIERNA_HPP
#define WYMIERNA_HPP

#include "wyjatki.hpp"
#include <iostream>

namespace obliczenia {

class wymierna {
    int licz, mian;
    void skracaj();

public:
    wymierna() noexcept; 
    wymierna(int l, int m); //upraszczamy i skracamy
    wymierna(int x) noexcept; //konwertujemy z liczby calkowitej

    int licznik() const noexcept;
    int mianownik() const noexcept;

    wymierna& operator+=(const wymierna&) noexcept(false);
    wymierna& operator-=(const wymierna&) noexcept(false);
    wymierna& operator*=(const wymierna&) noexcept(false);
    wymierna& operator/=(const wymierna&) noexcept(false);

    wymierna operator-() const noexcept;
    wymierna operator!() const;

    operator double() const noexcept;
    explicit operator int() const noexcept;

    friend wymierna operator+(const wymierna&, const wymierna&) noexcept(false);
    friend wymierna operator-(const wymierna&, const wymierna&) noexcept(false);
    friend wymierna operator*(const wymierna&, const wymierna&) noexcept(false);
    friend wymierna operator/(const wymierna&, const wymierna&) noexcept(false);

    friend std::ostream& operator<<(std::ostream&, const wymierna&);
};

} 
#endif
