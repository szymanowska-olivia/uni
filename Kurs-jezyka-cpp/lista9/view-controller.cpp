#include "view-controller.hpp"
#include "wyjatek_samotnika.hpp"
#include <iostream>
#include <ctime> 

void ViewController::run() {
    // czas startu
    std::time_t start = std::time(nullptr);

    while (!model.isGameOver()) {
        displayBoard();
        try {
            std::string move = promptMove();
            if (move == "quit") break;
            model.move(move);
        } catch (const wyjatek_samotnika& ex) {
            std::cerr << "Blad: " << ex.what() << '\n';
        }
    }

    displayBoard();
    
    // czas konca
    std::time_t end = std::time(nullptr);

    double duration = std::difftime(end, start);


    std::cout << "\nGra zakonczona. Pozostalo pionkow: " << model.countPegs() << "\n";
    std::cout << (model.isWin() ? "Wygrana!" : "Przegrana.") << "\n";
    std::cout << "Czas gry: " << duration << " sekund.\n";
}

void ViewController::displayBoard() {
    std::cout << "  A B C D E F G\n";
    const auto& board = model.getBoard();
    for (int i = 0; i < 7; ++i) {
        std::cout << i + 1 << ' ';
        for (int j = 0; j < 7; ++j) {
            if (board[i][j] == -1) std::cout << "  ";
            else if (board[i][j] == 0) std::cout << ". ";
            else if (board[i][j] == 1) std::cout << "O ";
        }
        std::cout << '\n';
    }
}

std::string ViewController::promptMove() {
    std::string input;
    std::cout << "Podaj ruch (np. F4L) albo wyjdz -> 'quit'): ";
    std::getline(std::cin, input);
    return input;
}
