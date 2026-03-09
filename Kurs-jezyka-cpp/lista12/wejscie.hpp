#ifndef WEJSCIE_HPP
#define WEJSCIE_HPP

#include <fstream>
#include <string>

class Wejscie {
    std::ifstream plik;
    int klucz;

    std::string deszyfruj(const std::string& tekst) const;

public:
    explicit Wejscie(const std::string& nazwa_pliku);
    ~Wejscie();

    void ustawKlucz(int k);
    std::string czytaj();
    friend Wejscie& operator>>(Wejscie& w, std::string& linia);
};

#endif
