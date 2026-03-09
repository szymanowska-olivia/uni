#include "kolejka.hpp"
#include "punkt.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
    kolejka k(2); 
    kolejka k4({punkt(1,2),punkt(3,4),punkt(5,6)});
    try {
        k.wstaw(punkt(1, 2));
        k.wstaw(punkt(3, 4));
        k.wstaw(punkt(5, 6));  

    } catch (const overflow_error& e) {
        cout << "Błąd: " << e.what() << endl;
    }

    try {
        cout << "długość: " << k.dlugosc() << endl;

        punkt p = k.zprzodu();
        cout << "punkt z poczatku: (" << p.getX() << ", " << p.getY() << ")" << endl;

        k.usun();
        cout << "długość: " << k.dlugosc() << endl;
    } catch (const exception& e) {
        cout << "Błąd: " << e.what() << endl;
    }

    kolejka k2 = k;  
    cout << "długość k2: " << k2.dlugosc() << endl;

    kolejka k3 = std::move(k);  
    cout << "długość k3: " << k3.dlugosc() << endl;
    cout << "długość k: " << k.dlugosc() << endl;

    cout << k4.dlugosc()<<endl;

    return 0;
}
