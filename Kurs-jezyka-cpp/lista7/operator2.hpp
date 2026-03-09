#ifndef OPERATOR2_HPP
#define OPERATOR2_HPP

#include "operator.hpp"

namespace obliczenia {

class Operator2 : public Operator {
public:
    Operator2(Wyrazenie* l, Wyrazenie* p);
    virtual ~Operator2();
};

}

#endif
