#ifndef WYJATEK_INVALIDMOVE_HPP
#define WYJATEK_INVALIDMOVE_HPP

#include "wyjatek_samotnika.hpp"

class wyjatek_invalidmove : public wyjatek_samotnika {
public:
    explicit wyjatek_invalidmove(const std::string& msg);
};

#endif