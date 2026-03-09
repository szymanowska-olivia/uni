#include <iostream>
#include "wielom.hpp"

using namespace std;

int main() {
    // konstruktory
    wielom w1;
    cout << "w1 stopień: " << w1.stopien() << endl;

    wielom w2(3, 2.5);
    cout << "w2 stopień = " << w2.stopien() << endl;

    double wsp[] = {1.0, -2.0, 3.0, -4.0};
    wielom w3(3, wsp); 
    cout << "w3 stopień = " << w3.stopien() << endl;

    wielom w4({1, -2, 3, -4.1, 21.8});
    cout << "w4 stopień = " << w4.stopien() << endl;

    //operatory[]
    cout << "w2[2] = " << w2[2] << endl; 
    cout << "w3[2] = " << w3[2] << endl; 

    try {
        cout << "w2[4] = " << w2[4] << endl; 
    } catch (const out_of_range &e) {
        cout << "Błąd: " << e.what() << endl;
    }

    //operator >> <<
    cout << "w5 stopien i wspolczynniki:" << endl;
    wielom w5;
    cin >> w5;  
    cout << "w5: " << w5 << endl;

    //operatory arytmetyczne
    wielom w6 = w2 + w3;
    cout << "w2 + w3: " << w6 << endl;
    wielom w7 = w2 - w3;
    cout << "w2 - w3: " << w7 << endl;
    wielom w8 = w2 * w3;
    cout << "w2 * w3: " << w8 << endl;
    wielom w9 = w2 * 2.0;
    cout << "w2 * 2.0: " << w9 << endl;

    //operatory +=, -=, *=
    w2 += w3;
    cout << "w2 += w3: " << w2 << endl;
    w2 -= w3;
    cout << "w2 -= w3: " << w2 << endl;
    w2 *= w3;
    cout << "w2 *= w3: " << w2 << endl;
    w2 *= 3.0;
    cout << "w2 *= 3.0: " << w2 << endl;

    //operator ()
    double wynik = w2(2);
    cout << "w2(2) = " << wynik << endl;

    //konstruktor kopiujący i przenoszacy i operatory
    wielom w10 = w2; 
    cout << "w10: " << w10 << endl;
    w2 = w3;
    cout << "w2: " << w2 << endl;
    w2 = std::move(w3);
    cout << "w2: " << w2 << endl;

    return 0;
}
