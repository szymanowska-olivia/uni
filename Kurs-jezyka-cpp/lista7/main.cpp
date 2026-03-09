#include <iostream>
#include "liczba.hpp"
#include "stala.hpp"
#include "zmienna.hpp"
#include "wszystkie_operatory.hpp"

using namespace std;
using namespace obliczenia;

int main() {
    Zmienna::ustaw("x", 4);
    Zmienna::ustaw("y", 2);

    Wyrazenie* w = new Potega(
        new Liczba(2),
        new Odejmowanie(
            new Dzielenie(
                new Zmienna("x"),
                new Liczba(3)
            ),
            new Liczba(1)
        )
    );

    std::cout << "Wyrazenie: " << w->zapis() << std::endl;
    std::cout << "Wynik: " << w->oblicz() << std::endl;

    Wyrazenie* w2 = new Mnozenie(
        new Dodawanie(
            new Liczba(5),
            new Zmienna("y")
        ),
        new Odejmowanie(
            new Zmienna("x"),
            new Liczba(2)
        )
    );
    std::cout << "Wyrazenie: " << w2->zapis() << std::endl;
    std::cout << "Wynik: " << w2->oblicz() << std::endl;

    Wyrazenie* w7 = new Dodawanie(
        new Zero(),
        new Jeden()
    );
    std::cout << "Wyrazenie: " << w7->zapis() << std::endl;
    std::cout << "Wynik: " << w7->oblicz() << std::endl;

    try {
        // Dzielenie przez zero
        Wyrazenie* dzielenieZero = new Dzielenie(
            new Liczba(5),
            new Zero()
        );
        cout << dzielenieZero->zapis() << " = " << dzielenieZero->oblicz() << endl;
        delete dzielenieZero;
    } catch (const exception& e) {
        cout << "Wyjatek: " << e.what() << endl;
    }

    delete w;
    delete w2;
    delete w7;
    
}
