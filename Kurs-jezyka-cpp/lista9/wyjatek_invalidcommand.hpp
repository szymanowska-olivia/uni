#ifndef WYJATEK_INVALIDCOMMAND_HPP
#define WYJATEK_INVALIDCOMMAND_HPP

#include "wyjatek_samotnika.hpp"

class wyjatek_invalidcommand : public wyjatek_samotnika {
public:
    explicit wyjatek_invalidcommand(const std::string& msg);
};
#endif