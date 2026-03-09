#ifndef WYRAZENIE_HPP
#define WYRAZENIE_HPP

#include <string>

class Wyrazenie {
public:
    virtual int oblicz() const = 0;
    virtual std::string zapis() const = 0;
    virtual int priorytet() const = 0;
    virtual ~Wyrazenie() = default;

};

#endif