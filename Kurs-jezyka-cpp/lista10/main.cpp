#include <iostream>
#include <climits>
#include "wymierna.hpp"
#include "wyjatki.hpp"

using namespace obliczenia;
using namespace std;

int main() {
    try {
        wymierna a;                // domyślny 0/1
        wymierna b(3);             // konwersja z int
        wymierna c(6, 8);          // uproszczenie
        wymierna d(-2, -5);        // znak do licznika
        wymierna e(5, -10);       
        
        cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << ", e = " << e << endl;

        //przypisujace
        wymierna f(1, 2);
        cout << "f = " << f << endl;
        f += wymierna(1, 3);  
        cout << "f += 1/3 = " << f << endl;
        f -= wymierna(1, 6);  
        cout << "f -= 1/6 = " << f << endl;
        f *= wymierna(3, 4);  
        cout << "f *= 3/4 = " << f << endl;
        f /= wymierna(2, 5);  
        cout << "f /= 2/5 = " << f << endl;

        //zwykle
        wymierna g = wymierna(2, 3) + wymierna(1, 6); 
        cout << "2/3 + 1/6 = " << g << endl;
        wymierna h = wymierna(3, 4) - wymierna(1, 4); 
        cout << "3/4 - 1/4 = " << h << endl;
        wymierna i = wymierna(2, 3) * wymierna(3, 2); 
        cout << "2/3 * 3/2 = " << i << endl;
        wymierna j = wymierna(4, 5) / wymierna(2, 3); 
        cout << "4/5 / 2/3 = " << j << endl;

        //unarne
        wymierna k = -wymierna(3, 7);
        cout << "-(3/7) = " << k << endl;
        wymierna l = !wymierna(2, 5);
        cout << "!(2/5) = " << l << endl;

        wymierna m(5, 2);
        double dval = m;
        int ival = static_cast<int>(m);
        cout << "double(5/2) = " << dval << ", int(5/2) = " << ival << endl;

        wymierna n = m;         //kopiujący
        wymierna o(1, 2);
        o = n;                  //przypisania
        cout << "n = " << n << ", o = " << o << endl;

        //czesc okresowa
        wymierna p(1, 3);      
        wymierna q(2359348, 99900); 
        cout << "1/3 = " << p << endl;
        cout << "2359348/99900 = " << q << endl;

        try {
            wymierna x(1, 0);  // dzielenie przez 0
        } catch (const dzielenie_przez_0& e) {
            cout << "Wyjątek: " << e.what() << endl;
        }

        try {
            wymierna y(1, 2);
            y /= wymierna(0);  // dzielenie przez 0
        } catch (const dzielenie_przez_0& e) {
            cout << "Wyjątek: " << e.what() << endl;
        }

        try {
            //przekroczenie zakresu
            wymierna big(INT_MAX, 1);
            big += wymierna(1, 1);
        } catch (const przekroczenie_zakresu& e) {
            cout << "Wyjątek: " << e.what() << endl;
        }

    } catch (const std::exception& e) {
        cout << "Wyjątek: " << e.what() << endl;
    }

}
