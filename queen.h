#pragma once

#include <iostream>

class PointInteger;
struct Board;

class Queen {
    public:
    Queen(int, Queen*);

    bool FindSolution(int);
    bool Advance(int);
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

/*
bool FixFlow()
{
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        fflush(stdin);
        return true;
        //        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
        return false;
    }
}


template <typename T>
void Input(T& side1, const std::string& message)
{
    do
    {
        std::cout << message << '\n';
        std::cin >> side1;
    } while (FixFlow());
}
*/