#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "wyrazenie.hpp"

class Operator : public Wyrazenie {
protected:
    Wyrazenie* lewy;
    Wyrazenie* prawy;

    std::string nawias(Wyrazenie* wyrazenie, bool prawa_strona) const;
public:
    Operator(Wyrazenie* l, Wyrazenie* p);
    virtual ~Operator();
};

#endif
