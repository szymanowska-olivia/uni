#include "kolo.h"
#include "prosta.h"
#include <cmath>
#include <stdexcept>

Kolo::Kolo() : srodek(Punkt(0, 0)), promien(1.0) {}

Kolo::Kolo(Punkt srodek, double promien) {
    if (promien <= 0) {
        throw std::invalid_argument("Promien nie moze byc mniejszy lub rowny zero.");
    }
    this->srodek = srodek;
    this->promien = promien;
}

Punkt Kolo::getSrodek() const {
    return srodek;
}

double Kolo::getPromien() const {
    return promien;
}

void Kolo::setSrodek(const Punkt& srodek) {
    this->srodek = srodek;
}

void Kolo::setPromien(double promien) {
    if (promien <= 0) {
        throw std::invalid_argument("Promien nie moze byc mniejszy lub rowny zero.");
    }
    this->promien = promien;
}

double Kolo::obwod() const {
    return 2 * M_PI * promien;
}

double Kolo::pole() const {
    return M_PI * std::pow(promien, 2);
}

bool Kolo::czyNalezy(const Punkt& p) const {
    return Punkt::odleglosc(srodek, p) <= promien;
}

bool Kolo::czyZawieraSie(const Kolo& k1, const Kolo& k2) {
    double odlegloscSrodkow = Punkt::odleglosc(k1.getSrodek(), k2.getSrodek());
    return odlegloscSrodkow + k2.getPromien() <= k1.getPromien();
}

bool Kolo::czyRozlaczne(const Kolo& k1, const Kolo& k2) {
    double odlegloscSrodkow = Punkt::odleglosc(k1.getSrodek(), k2.getSrodek());
    return odlegloscSrodkow > k1.getPromien() + k2.getPromien();
}

void Kolo::translacja(double dx, double dy) {
    srodek.translacja(dx, dy);
}

void Kolo::obrót(double kat, const Punkt& srodekObrotu) {
    srodek.obrót(kat, srodekObrotu);
}

void Kolo::symetriaSrodkowa(const Punkt& srodek) {
    this->srodek.symetriaSrodkowa(srodek);
}

void Kolo::symetriaOsiowa(const class Prosta& p) {
    srodek.symetriaOsiowa(p);
}
