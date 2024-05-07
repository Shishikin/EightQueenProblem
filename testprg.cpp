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
    
    // для сортировки
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
    

    // надо сделать подгон на +7 для столбцов и прочее

    bool IsRotate(Board other) const
    {   
        Board board90 = other;
        for (int f = 0; f < 4; ++f)
        {
            board90 = board90.Rotate(M_PI / 2);
            for (int i = 0; i < board90.board.size(); ++i)
            {
                board90.board[i].x += 7;
            }
            if (*this == board90)
            {
                return true;
            }
        }        
        return false;         
    }
    
};




void Queen::Boards(Board& boards, int index)
{
    if (pNeighbor)
        pNeighbor->Boards(boards, index + 1);
    boards.board[index].x = row;
    boards.board[index].y = column;
//        std::cout << "Строка: " << row << "; Cтолбец: " << column << "\n";
}





/* Эта программа находит все решения задачи о восьми ферзях. */
int main() 
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    int limit = 8;
//    Input(limit, "Введите размер доски ");

    limit = limit - 1;
    Board board = Board(limit+1);
    std::vector<Board> boards;
    std::vector<Board> noRotationBoard;


    int count = 0;
    Queen* pLastQueen = NULL;
    for (int i = 0; i <= limit; i++) 
    {
        // Создать и инициализировать нового ферзя в i-м столбце
        pLastQueen = new Queen(i, pLastQueen);        
        if (!pLastQueen->FindSolution(limit))
            std::cout << "Нет решения.\n";
    }
 
    do
    {
        pLastQueen->Print(std::cout, count);
        boards.push_back(board);
        pLastQueen->Boards(boards[count], 0);
        ++count;
    } while (pLastQueen->Advance(limit));
 
    
    
    for (int i = 0; i < 92; ++i)
    {
        std::cout << "Решение " << i << '\n';
        std::cout << boards[i] << '\n';
    }

    std::cout << boards[40].Rotate(M_PI);
 //     std::cout << boards[4].Rotate(M_PI);
 //   std::cout << boards[4].IsRotate(boards[40]);
 //   std::cout << boards[27].IsRotate(boards[4]);
 //   std::cout << boards[35].IsRotate(boards[27]);
 //   std::cout << boards[40].IsRotate(boards[35]);




    noRotationBoard.push_back(boards[0]);
    std::vector<Board> boardNoRotate;
    boardNoRotate.push_back(boards[0]);
    
    count = 0;
    for (int i = 1; i < 92; ++i)
    {
        bool flag = 1;
        for (int k = 0; k < boardNoRotate.size(); ++k)
        {
            if (
                boards[i].IsRotate(boardNoRotate[k])
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

 //   std::cout << IsRotate(boards[64], boards[4]);

    

    for (int i = 0; i < 92; ++i)
    {
        std::cout << "Решение " << i << '\n';
        std::cout << boards[i] << '\n';
    }
    
    for (int k = 0; k < boardNoRotate.size(); ++k)
    {
        std::cout << "Решение без поворотов" << k << '\n';
        std::cout << boardNoRotate[k] << '\n';
    }
    
    
    
    // Удаление объектов-ферзей
    while (pLastQueen) 
    {
        Queen* pPrevQueen = pLastQueen->GetNeighbor();
        delete pLastQueen;
        pLastQueen = pPrevQueen;
    }
    

    return 0;
}

