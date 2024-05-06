#include "queen.h"

Queen::Queen(int col, Queen* pNgb)
    : column(col), pNeighbor(pNgb), row(0) {}

bool Queen::FindSolution() 
{
    if (pNeighbor)
        if (pNeighbor->CanAttack(row, column))
            return Advance();
    return true;
}

bool Queen::Advance() 
{
    // ������� ������������� �� ��������� ������
    if (row < 7) 
    {
        row++;
        return FindSolution();
    }
    // ���� ����� ����� �� ��������� ������, �� ����
    // ���������� �������� ������ � ���������� �������
    if (pNeighbor)
        if (pNeighbor->Advance()) 
        {
            // �������� ����� � 1-� ������
            row = 0;
            return FindSolution();
        }
    return false;
}

void Queen::Print(std::ostream& os, int count) const 
{
    if (pNeighbor)
        pNeighbor->Print(os, count);
    if (column == 0) 
    {
        os << "������� #" << count << '\n';
    }
    os << "|---|---|---|---|---|---|---|---|\n";
    os << '|';

    for (int i = 0; i <= 7; i++) 
    {
        os << (i == row ? " O |" : "   |");
    }
    os << '\n';
    if (column == 7) {
        os << "|---|---|---|---|---|---|---|---|\n";
    }
}



bool Queen::CanAttack(int r, int c) const 
{
    // �������� �� �� �� ������
    if (row == r)
        return true;
    // �������� ���������
    int deltaCol = c - column;
    if (row + deltaCol == r || row - deltaCol == r)
        return true;
    // ��������, ����� �� ���� ������ (r, c) ������
    if (pNeighbor)
        return pNeighbor->CanAttack(r, c);
    return false;
}

