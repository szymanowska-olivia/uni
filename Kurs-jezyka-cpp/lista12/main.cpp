#include <iostream>
#include "wejscie.hpp"
#include "wyjscie.hpp"
#include "manipulatory.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Blad\n";
        return 1;
    }

    std::string plik_we = argv[1];
    std::string plik_wy = argv[2];
    int klucz_wartosc = std::stoi(argv[3]);

    try {
        Wejscie wejscie(plik_we);
        Wyjscie wyjscie(plik_wy);

        klucz(wejscie, 0);
        klucz(wyjscie, klucz_wartosc);

        std::string linia;
        while (1) {
            try {
                wejscie >> linia;
            } catch (std::ios_base::failure&) {
                break;
            }
            wyjscie << linia;
        }

    } catch (const std::exception& e) {
        std::cerr << "Blad: " << e.what() << std::endl;
        return 1;
    }

}
