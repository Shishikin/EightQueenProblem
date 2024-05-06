#pragma once

#include <iostream>

class PointInteger;
struct Board;

class Queen {
    public:
    Queen(int, Queen*);

    bool FindSolution();
    bool Advance();
    void Print(std::ostream&, int) const;
    void Boards(Board& board, int index);

    Queen* GetNeighbor() {
        return pNeighbor;
    }

    private:
    const int column; // Номер столбца (от 1 до 8)
    int row;          // Номер строки (от 1 до 8)
    Queen* pNeighbor; // Указатель на ферзя-соседа слева

    bool CanAttack(int r, int c) const;
};
