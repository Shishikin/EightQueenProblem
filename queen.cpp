#include "queen.h"

Queen::Queen(int col, Queen* pNgb)
    : column(col), pNeighbor(pNgb), row(0) {}

bool Queen::FindSolution(int limit) 
{
    if (pNeighbor)
        if (pNeighbor->CanAttack(row, column))
            return Advance(limit);
    return true;
}

bool Queen::Advance(int limit) 
{
    // ������� ������������� �� ��������� ������
    if (row < limit)
    {
        row++;
        return FindSolution(limit);
    }
    // ���� ����� ����� �� ��������� ������, �� ����
    // ���������� �������� ������ � ���������� �������
    if (pNeighbor)
        if (pNeighbor->Advance(limit))
        {
            // �������� ����� � 1-� ������
            row = 0;
            return FindSolution(limit);
        }
    return false;
}

void Queen::Print(std::ostream& os, int count, int limit) const 
{
    if (pNeighbor)
        pNeighbor->Print(os, count, limit);
    if (column == 0) 
    {
        os << "������� #" << count << '\n';
    }
    os << "|---|---|---|---|---|---|---|---|\n";
    os << '|';

    for (int i = 0; i <= limit; i++) 
    {
        os << (i == row ? " O |" : "   |");
    }
    os << '\n';
    if (column == limit) {
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

