#ifndef WYJSCIE_HPP
#define WYJSCIE_HPP

#include <fstream>
#include <string>

class Wyjscie {
    std::ofstream plik;
    int klucz;

    std::string szyfruj(const std::string& tekst) const;

public:
    explicit Wyjscie(const std::string& nazwa_pliku);
    ~Wyjscie();

    void ustawKlucz(int k);
    void pisz(const std::string& tekst);

    friend Wyjscie& operator<<(Wyjscie& w, const std::string& tekst);
};

#endif
