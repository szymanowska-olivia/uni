#include "wyjatek_samotnika.hpp"

wyjatek_samotnika::wyjatek_samotnika(const std::string& msg)
    : std::logic_error(msg) {} //dziedizczenie po logic error