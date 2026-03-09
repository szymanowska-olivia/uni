#ifndef VIEW_CONTROLLER_HPP
#define VIEW_CONTROLLER_HPP

#include "model.hpp"
#include <string>

class ViewController {
public:
    void run();

private:
    Model model; //stan gry
    void displayBoard();
    std::string promptMove(); 
};

#endif