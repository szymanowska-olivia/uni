#include "wymierna.hpp"
#include <numeric>
#include <cmath>
#include <map>
#include <sstream>
#include <limits>

namespace obliczenia {

int gcd(int a, int b) {
    if (b == 0) return abs(a);
    return gcd(b, a % b);
}


void wymierna::skracaj() {
    if (mian == 0) throw dzielenie_przez_0();
    if (mian < 0) {
        licz = -licz;
        mian = -mian;
    }
    int d = gcd(licz, mian);
    licz /= d;
    mian /= d;
}

wymierna::wymierna() noexcept : licz(0), mian(1) {}

wymierna::wymierna(int l, int m) : licz(l), mian(m) {
    skracaj();
}

wymierna::wymierna(int x) noexcept : licz(x), mian(1) {}

int wymierna::licznik() const noexcept { return licz; }
int wymierna::mianownik() const noexcept { return mian; }

wymierna& wymierna::operator+=(const wymierna& w) {
    long long l = static_cast<long long>(licz) * w.mian + static_cast<long long>(w.licz) * mian;
    long long m = static_cast<long long>(mian) * w.mian;
    if (l > std::numeric_limits<int>::max() || m > std::numeric_limits<int>::max())
        throw przekroczenie_zakresu();
    licz = static_cast<int>(l);
    mian = static_cast<int>(m);
    skracaj();
    return *this;
}

wymierna& wymierna::operator-=(const wymierna& w) {
    return *this += (-w);
}

wymierna& wymierna::operator*=(const wymierna& w) {
    long long l = static_cast<long long>(licz) * w.licz;
    long long m = static_cast<long long>(mian) * w.mian;
    if (l > std::numeric_limits<int>::max() || m > std::numeric_limits<int>::max())
        throw przekroczenie_zakresu();
    licz = static_cast<int>(l);
    mian = static_cast<int>(m);
    skracaj();
    return *this;
}

wymierna& wymierna::operator/=(const wymierna& w) {
    return *this *= !w;
}

wymierna wymierna::operator-() const noexcept {
    return wymierna(-licz, mian);
}

wymierna wymierna::operator!() const {
    if (licz == 0) throw dzielenie_przez_0();
    return wymierna(mian * (licz < 0 ? -1 : 1), std::abs(licz));
}

wymierna::operator double() const noexcept {
    return static_cast<double>(licz) / mian;
}

wymierna::operator int() const noexcept {
    return static_cast<int>(std::round(static_cast<double>(*this)));
}

wymierna operator+(const wymierna& a, const wymierna& b) {
    wymierna tmp = a;
    tmp += b;
    return tmp;
}

wymierna operator-(const wymierna& a, const wymierna& b) {
    return a + (-b);
}

wymierna operator*(const wymierna& a, const wymierna& b) {
    wymierna tmp = a;
    tmp *= b;
    return tmp;
}

wymierna operator/(const wymierna& a, const wymierna& b) {
    wymierna tmp = a;
    tmp /= b;
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const wymierna& w) {
    int whole = w.licz / w.mian;
    int rem = std::abs(w.licz % w.mian);
    std::ostringstream frac;
    std::string part;
    int base = w.mian;
    std::map<int, int> seen;

    int pos = 0;
    while (rem != 0 && seen.find(rem) == seen.end()) { // pętla dopóki reszta nie jest zerem
        seen[rem] = pos++; //na ktorej pozycji pojawila sie reszta
        rem *= 10;
        part += ('0' + rem / base); //dodajemy kolejna cyfre
        rem %= base;
    }

    if (rem == 0) { //ułamek skończony
        if (w.licz < 0) os << "-";
        os << whole;
        if (!part.empty()) os << "." << part;
    } else { //powtórzona reszta ułamek okresowy
        int start = seen[rem];
        if (w.licz < 0) os << "-";
        os << whole << "." << part.substr(0, start) << "(" << part.substr(start) << ")";
    }

    return os;
}

}
