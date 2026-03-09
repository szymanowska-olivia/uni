#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <string>

class Model {
public:
    Model();

    bool isGameOver() const;
    bool isWin() const;
    int countPegs() const;
    void move(const std::string& command);
    const std::vector<std::vector<int>>& getBoard() const;

private:
    std::vector<std::vector<int>> board;
    void parseMove(const std::string& cmd, int& row, int& col, char& dir);
    void validateMove(int row, int col, char dir);
    void applyMove(int row, int col, char dir);
};

#endif
