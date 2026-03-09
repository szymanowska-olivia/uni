#include <iostream>
#include "punkt.h"
#include "kolo.h"
#include "wektor.h"
#include "prosta.h"

using namespace std;

int main() {
    try {
        Punkt p1(3, 4);
        Punkt p2(7, 1);

        cout << "Odleglosc miedzy punktami: " << Punkt::odleglosc(p1, p2) << endl;

        Kolo k1(p1, 5);
        Kolo k2(p2, 3);

        cout << "Obwod kola k1: " << k1.obwod() << endl;
        cout << "Pole kola k1: " << k1.pole() << endl;

        cout << "Czy punkt p2 nalezy do kola k1? " << (k1.czyNalezy(p2) ? "Tak" : "Nie") << endl;

        cout << "Czy kolo k1 zawiera kolo k2? " << (Kolo::czyZawieraSie(k1, k2) ? "Tak" : "Nie") << endl;

        cout << "Czy kolo k1 i kolo k2 sa rozlaczne? " << (Kolo::czyRozlaczne(k1, k2) ? "Tak" : "Nie") << endl;

        k1.translacja(2, 3);
        cout << "Nowa pozycja kola k1 po translacji: (" << k1.getSrodek().getX() << ", " << k1.getSrodek().getY() << ")" << endl;

        p1.obrót(90, Punkt(0, 0));
        cout << "Nowa pozycja punktu p1 po obrocie o 90 stopni wokol punktu (0,0): (" << p1.getX() << ", " << p1.getY() << ")" << endl;

    } catch (const exception& e) {
        cout << "Blad: " << e.what() << endl;
    }

    return 0;
}
