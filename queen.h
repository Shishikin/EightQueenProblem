#pragma once

#include <iostream>

class PointInteger;
struct Board;

class Queen {
    public:
    Queen(int, Queen*);

    bool FindSolution(int);
    bool Advance(int);
    void Print(std::ostream&, int, int) const;
    void Boards(Board& board, int index);

    Queen* GetNeighbor() {
        return pNeighbor;
    }

    private:
    const int column; // ����� ������� (�� 1 �� 8)
    int row;          // ����� ������ (�� 1 �� 8)
    Queen* pNeighbor; // ��������� �� �����-������ �����

    bool CanAttack(int r, int c) const;
};

