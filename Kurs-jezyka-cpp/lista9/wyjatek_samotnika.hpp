#ifndef WYJATEK_SAMOTNIKA_HPP
#define WYJATEK_SAMOTNIKA_HPP

#include <stdexcept>

class wyjatek_samotnika : public std::logic_error {
public:
    explicit wyjatek_samotnika(const std::string& msg); //konstruktor
};

#endif