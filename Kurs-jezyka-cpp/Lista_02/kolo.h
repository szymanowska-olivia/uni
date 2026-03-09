#ifndef KOLO_H
#define KOLO_H

#include "punkt.h"
#include <stdexcept>

class Kolo {
private:
    Punkt srodek;
    double promien;

public:
    Kolo();
    Kolo(Punkt srodek, double promien);
    Punkt getSrodek() const;
    double getPromien() const;
    void setSrodek(const Punkt& srodek);
    void setPromien(double promien);
    double obwod() const;
    double pole() const;
    bool czyNalezy(const Punkt& p) const;
    static bool czyZawieraSie(const Kolo& k1, const Kolo& k2);
    static bool czyRozlaczne(const Kolo& k1, const Kolo& k2);
    void translacja(double dx, double dy);
    void obrót(double kat, const Punkt& srodek);
    void symetriaSrodkowa(const Punkt& srodek);
    void symetriaOsiowa(const class Prosta& p);
};

#endif
