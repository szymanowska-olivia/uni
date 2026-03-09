#include "model.hpp"
#include "wyjatek_invalidmove.hpp"
#include "wyjatek_invalidcommand.hpp"

Model::Model() : board(7, std::vector<int>(7, -1)) { //1 = pionek / 0 = puste / -1 = za plansza
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j)
            if ((i >= 2 && i <= 4) || (j >= 2 && j <= 4))
                board[i][j] = 1;
    board[3][3] = 0;
}

bool Model::isGameOver() const {
    for (int r = 0; r < 7; ++r) {
        for (int c = 0; c < 7; ++c) {
            if (board[r][c] != 1) continue; //pola nie majace pionkow
            if (r >= 2 && board[r-1][c] == 1 && board[r-2][c] == 0) return false;
            if (r <= 4 && board[r+1][c] == 1 && board[r+2][c] == 0) return false;
            if (c >= 2 && board[r][c-1] == 1 && board[r][c-2] == 0) return false;
            if (c <= 4 && board[r][c+1] == 1 && board[r][c+2] == 0) return false;
        }
    }
    return true; //nie ma wiecej ruchow czyli nastepuje koniec gry
}

bool Model::isWin() const {
    return countPegs() == 1 && board[3][3] == 1;
}

int Model::countPegs() const {
    int count = 0;
    for (const auto& row : board)
        for (auto cell : row)
            if (cell == 1) ++count;
    return count;
}

void Model::move(const std::string& command) {
    int row, col;
    char dir;
    parseMove(command, row, col, dir);
    validateMove(row, col, dir);
    applyMove(row, col, dir);
}

const std::vector<std::vector<int>>& Model::getBoard() const {
    return board;
}

void Model::parseMove(const std::string& cmd, int& row, int& col, char& dir) {
    if (cmd.length() != 3)
        throw wyjatek_invalidcommand("Nieprawidlowe polecenie: " + cmd);
    col = toupper(cmd[0]) - 'A';
    row = cmd[1] - '1';
    dir = toupper(cmd[2]);
    if (row < 0 || row >= 7 || col < 0 || col >= 7)
        throw wyjatek_invalidcommand("Nieprawidlowe wspolrzedne: " + cmd);
}

void Model::validateMove(int row, int col, char dir) {
    int dr = 0, dc = 0;
    if (dir == 'U') dr = -1;
    else if (dir == 'D') dr = 1;
    else if (dir == 'L') dc = -1;
    else if (dir == 'R') dc = 1;
    else throw wyjatek_invalidcommand("Nieprawidlowy kierunek ruchu.");

    int midR = row + dr;
    int midC = col + dc;
    int endR = row + 2 * dr;
    int endC = col + 2 * dc;

    if (endR < 0 || endR >= 7 || endC < 0 || endC >= 7)
        throw wyjatek_invalidmove("Ruch poza plansza.");
    if (board[row][col] != 1 || board[midR][midC] != 1 || board[endR][endC] != 0)
        throw wyjatek_invalidmove("Nieprawidlowy ruch.");
}

void Model::applyMove(int row, int col, char dir) {
    int dr = 0, dc = 0;
    if (dir == 'U') dr = -1;
    else if (dir == 'D') dr = 1;
    else if (dir == 'L') dc = -1;
    else if (dir == 'R') dc = 1;

    board[row][col] = 0;
    board[row + dr][col + dc] = 0;
    board[row + 2 * dr][col + 2 * dc] = 1;
}
