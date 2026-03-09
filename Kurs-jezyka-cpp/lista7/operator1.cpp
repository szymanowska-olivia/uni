#include "operator1.hpp"

namespace obliczenia {

Operator1::Operator1(Wyrazenie* o) {
    operand = o;
}
Operator1::~Operator1() {
    delete operand;
}

}
