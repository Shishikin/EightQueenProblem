#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "queen.h"

#ifdef _WIN32
#include <Windows.h>
#endif

const double M_PI = 3.14159265358979323846;

class PointInteger
{
public:

    int x = 0;
    int y = 0;

    PointInteger(int x_, int y_) { x = x_; y = y_; }

    PointInteger Rotate(double rad)
    {
        int x_ = x * round(cos(rad)) - y * round(sin(rad));
        int y_ = x * round(sin(rad)) + y * round(cos(rad));
        return PointInteger(x_, y_);
    }
    
    bool operator ==(const PointInteger& other)
    {
        return (x == other.x && y == other.y) ? true : false;
    }
    
    // ��� ����������
    bool operator<(const PointInteger& other) const
    {
        if (x < other.x)
        {
            return true;
        }
        else
        {
            if (x > other.x)
            {
                return false;
            }
            else
            {
                if (y < other.y)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    friend std::ostream& operator <<(std::ostream& out, const PointInteger& point)
    {
        out << point.x << '\t' << point.y << '\n';
        return out;
    }
};

struct Board
{

    std::vector<PointInteger> board;

    Board(){}

    Board(int size)
    {
        for (int i = 0; i < size; ++i)
        {
            Push(PointInteger(0, 0));
        }
    }

    Board Rotate(double rad)
    {
        Board board_;
        for (auto a : board)
        {
            board_.Push(a.Rotate(rad));
        }
        return board_;
    }
        
    
    void Push(const PointInteger& a)
    {
        board.push_back(a);
    }
    

    bool operator ==(const Board& other)
    {
        Board b1 = *this;
        Board b2 = other;
        std::sort(b1.board.begin(), b1.board.end());
        std::sort(b2.board.begin(), b2.board.end());
        for (int i = 0; i < board.size(); ++i)
        {
            if ( !(b1.board[i] == b2.board[i]) )
            {
                return false;
            }            
        }
        return true;
    }
    
    friend std::ostream& operator <<(std::ostream& out, const Board& boards)
    {
        

        for (int i = 0; i < boards.board.size(); ++i)
        {
            out << boards.board[i];
        }
        return out;
    }

    // ���� ������� ������ �� +7 ��� �������� � ������
/*
    bool IsRotate(Board other) const
    {   
        Board board90 = other;
        board90 = board90.Rotate(M_PI / 2);
        for (int i = 0; i < board90.board.size(); ++i)
        {
            board90.board[i].x += 7;
        }
        if (*this == board90)
        {
            return true;
        }
        return false;
        /*
        if (*this == other.Rotate(1.57)
            || *this == other.Rotate(3.14)
            || *this == other.Rotate(4.71))
        {
            return true;
        }
        else
        {
            return false;
        }
        */
 //   }
    
};

bool IsRotate(Board a, Board other) 
{
    int r = 0;
    Board board90 = other;
    board90 = board90.Rotate(M_PI / 2);
    
    for (int i = 0; i < board90.board.size(); ++i)
    {
        board90.board[i].x = abs(board90.board[i].x);
    }/*
    for (int i = 0; i < board90.board.size(); ++i)
    {
        r = board90.board[i].x;
        board90.board[i].x = board90.board[i].y;
        board90.board[i].y = r;
    }*/
    if (a == board90)
    {
        return true;
    }
    return false;
}
    /*
    if (*this == other.Rotate(1.57)
        || *this == other.Rotate(3.14)
        || *this == other.Rotate(4.71))
    {
        return true;
    }
    else
    {
        return false;
    }
    */
    //   }


void Queen::Boards(Board& boards, int index)
{
    if (pNeighbor)
        pNeighbor->Boards(boards, index + 1);
    boards.board[index].x = row;
    boards.board[index].y = column;
//        std::cout << "������: " << row << "; C������: " << column << "\n";
}





/* ��� ��������� ������� ��� ������� ������ � ������ ������. */
int main() 
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    Board board = Board(8);
    std::vector<Board> boards;
    std::vector<Board> noRotationBoard;
    for (int i = 0; i < 92; ++i)
    {
        boards.push_back(board);
    }

    int count = 0;
    Queen* pLastQueen = NULL;
    for (int i = 0; i <= 7; i++) 
    {
        // ������� � ���������������� ������ ����� � i-� �������
        pLastQueen = new Queen(i, pLastQueen);        
        if (!pLastQueen->FindSolution())
            std::cout << "��� �������.\n";
    }
    pLastQueen->Print(std::cout, count);
    pLastQueen->Boards(boards[count], 0);
    ++count;
 




 //   std::cout << board1.IsRotate(board1.Rotate(M_PI));

     

    while (pLastQueen->Advance())
    {
        pLastQueen->Print(std::cout, count);
        pLastQueen->Boards(boards[count], 0);
        ++count;
    }
    
    noRotationBoard.push_back(boards[0]);

    /*
    for (int i = 0; i < 92; ++i)
    {
        std::cout << "������� " << i << '\n';
        std::cout << boards[i] << '\n';
    }*/

    std::vector<Board> boardNoRotate;
    boardNoRotate.push_back(boards[0]);

    count = 0;
    for (int i = 1; i < 92; ++i)
    {
        bool flag = 1;
        for (int k = 0; k < boardNoRotate.size(); ++k)
        {
            if (
                IsRotate(boards[i], boardNoRotate[k])
                )
            {                   
                ++count;
                flag = 0;
            }
        }
        if (flag)
        {
            std::cout << "true " << i << '\n';
            boardNoRotate.push_back(boards[i]);
        }


        else
        {
            std::cout << "false " << i << '\n';
        }

        
    }


    std::cout << count << '\n';

  //  std::cout << IsRotate(boards[4], boards[64]);

    /*

    for (int i = 0; i < 92; ++i)
    {
        std::cout << "������� " << i << '\n';
        std::cout << boards[i] << '\n';
    }
    
    for (int k = 0; k < boardNoRotate.size(); ++k)
    {
        std::cout << "������� ��� ���������" << k << '\n';
        std::cout << boardNoRotate[k] << '\n';
    }

    */
    
    // �������� ��������-������
    while (pLastQueen) 
    {
        Queen* pPrevQueen = pLastQueen->GetNeighbor();
        delete pLastQueen;
        pLastQueen = pPrevQueen;
    }
    

    return 0;
}

