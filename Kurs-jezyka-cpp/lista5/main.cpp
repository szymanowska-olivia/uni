#include <iostream>
#include "kolor.hpp"
#include "kolornazwany.hpp"
#include "kolortransparentny.hpp"
#include "kolortransnaz.hpp"
#include "piksel.hpp"
#include "pikselkolorowy.hpp"

using namespace std;

int main() {
    
    //Kolor
    Kolor kolor1(100, 150, 200);
    cout << "Kolor1: R: " << kolor1.getRed()<< " G: " << kolor1.getGreen()<< " B: " << kolor1.getBlue() << endl;

    kolor1.rozjasnij(30);
    cout << "Kolor1: R: " << kolor1.getRed()<< " G: " << kolor1.getGreen()<< " B: " << kolor1.getBlue() << endl;

    kolor1.przyciemnij(50);
    cout << "Kolor1: R: " << kolor1.getRed()<< " G: " << kolor1.getGreen()<< " B: " << kolor1.getBlue() << endl;

    Kolor kolor2(50, 50, 50);
    cout << "Kolor2: R: " << kolor1.getRed()<< " G: " << kolor1.getGreen()<< " B: " << kolor1.getBlue() << endl;

    Kolor polaczony = Kolor::polacz(kolor1, kolor2);
    cout << "Kolor polaczony: R: " << kolor1.getRed()<< " G: " << kolor1.getGreen()<< " B: " << kolor1.getBlue() << endl;


    //KolorTrans
    KolorTransparentny kt(0, 255, 0, 128);
    cout << "Kolor: Alpha: " << kt.getAlpha() << " R: " << kt.getRed() << " G: " << kt.getGreen() << " B: " << kt.getBlue() << endl;

    kt.setAlpha(200);
    cout << "Kolor: Alpha: " << kt.getAlpha() << " R: " << kt.getRed() << " G: " << kt.getGreen() << " B: " << kt.getBlue() << endl;

    
    /*
    KolorTransNaz ktn1(100, 150, 200, 128, "niebieskawy");
    KolorTransNaz ktn2(200, 100, 50, 64, "czerwonawy");

    Kolor polaczonyktn = Kolor::polacz(ktn1, ktn2);
    unsigned short sredniaAlpha = (ktn1.getAlpha() + ktn2.getAlpha()) / 2;
    string polaczonaNazwa = ktn1.getNazwa() + "-" + ktn2.getNazwa();

    KolorTransNaz polaczony(polaczonyktn.getRed(), polaczonyktn.getGreen(), polaczonyktn.getBlue(), sredniaAlpha, polaczonaNazwa);

    cout << "Kolor polaczony: Nazwa: " << polaczony.getNazwa() 
        << " Alpha: " << polaczony.getAlpha() << " R: " << polaczony.getRed() << " G: " << polaczony.getGreen() << " B: " << polaczony.getBlue() << endl;
    */

    //Piksel
    Piksel p1(100, 200);

    cout << "Piksel p1: x: " << p1.getX() << " y: " << p1.getY() << endl;
    cout << "Odleglosc p1 od lewej: " << p1.odlegloscOdLewej() << endl;
    cout << "Odleglosc p1 od prawej: " << p1.odlegloscOdPrawej() << endl;
    cout << "Odleglosc p1 od gory: " << p1.odlegloscOdGory() << endl;
    cout << "Odleglosc p1 od dolu: " << p1.odlegloscOdDolu() << endl;

    Piksel p2(400, 300);

    cout << "Piksel p2: x: " << p2.getX() << " y: " << p1.getY() << endl;
    cout << "Odleglosc p2 od lewej: " << p2.odlegloscOdLewej() << endl;
    cout << "Odleglosc p2 od prawej: " << p2.odlegloscOdPrawej() << endl;
    cout << "Odleglosc p2 od gory: " << p2.odlegloscOdGory() << endl;
    cout << "Odleglosc p2 od dolu: " << p2.odlegloscOdDolu() << endl;

    double odlp12 = Piksel::odleglosc(p1, p2);
    cout << "Odleglosc miedzy p1 a p2: " << odlp12 << endl; //referencje

    double odlp12_ = Piksel::odleglosc(&p1, &p2);
    cout << "Odleglosc miedzy p1 a p2: " << odlp12_ << endl; //wskazniki

    //PikselKolorowy
    PikselKolorowy pk(10, 10, 20, 40, 60);
    cout << "Piksel pk: x: " << pk.getX() << " y: " << pk.getY() << " R: " << pk.getRed() << " G: " << pk.getGreen() << " B: " << pk.getBlue() << endl;

    pk.przesun(5, -5);
    pk.setRed(100);
    pk.setGreen(110);
    pk.setBlue(120);
    cout << "Piksel pk: x: " << pk.getX() << " y: " << pk.getY() << " R: " << pk.getRed() << " G: " << pk.getGreen() << " B: " << pk.getBlue() << endl;
    
    try{
    /*
    //KolorNazwany
    
     KolorNazwany cn2(255, 0, 0, "czerwony");
     cn2.setNazwa("bardzo czerwony");
     cout << "Kolor cn: Nazwa: " << cn2.getNazwa() << " R: " << cn2.getRed() << " G: " << cn2.getGreen() << " B: " << cn2.getBlue() << endl;
    */

    //KolorTransNaz
    KolorTransNaz ktn(10, 20, 30, 100, "szaroniebieski");
    cout << "Kolor ktn: Nazwa: " << ktn.getNazwa() << " Alpha: " << ktn.getAlpha() << " R: " << ktn.getRed() << " G: " << ktn.getGreen() << " B: " << ktn.getBlue() << endl;

    ktn.setNazwa("niebieskoszary");
    ktn.setAlpha(200);
    cout << "Kolor ktn: Nazwa: " << ktn.getNazwa() << " Alpha: " << ktn.getAlpha() << " R: " << ktn.getRed() << " G: " << ktn.getGreen() << " B: " << ktn.getBlue() << endl; 

    KolorTransNaz ktn21(10, 20, 30, 100, "Szaroniebieski");
    }
    catch (const exception &e){
        cout << "Błąd: " << e.what() << endl;
    }
    return 0;
}
