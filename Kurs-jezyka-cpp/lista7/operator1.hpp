#ifndef OPERATOR1_HPP
#define OPERATOR1_HPP

#include "wyrazenie.hpp"

namespace obliczenia {

class Operator1 : public Wyrazenie {
protected:
    Wyrazenie* operand;
public:
    Operator1(Wyrazenie* o);
    virtual ~Operator1();
};

}

#endif
