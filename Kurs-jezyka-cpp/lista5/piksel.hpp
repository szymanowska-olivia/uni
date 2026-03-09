#ifndef PIKSEL_HPP
#define PIKSEL_HPP

class Piksel {
private:
    int x;
    int y;
protected:
    static const int SZEROKOSC_EKRANU = 1920, WYSOKOSC_EKRANU = 1080; // HDTV1080
public:
    Piksel();
    Piksel(int x, int y);

    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;

    int odlegloscOdLewej() const;
    int odlegloscOdPrawej() const;
    int odlegloscOdGory() const;
    int odlegloscOdDolu() const;

    static double odleglosc(const Piksel& p1, const Piksel& p2);
    static double odleglosc(const Piksel* p1, const Piksel* p2);
};

#endif
