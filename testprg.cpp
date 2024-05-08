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

class PointInteger
{
public:

    int x = 0;
    int y = 0;

    PointInteger(int x_, int y_) { x = x_; y = y_; }

    // ������� ����� ������ ��� �� �������� ����
    PointInteger Rotate(const double rad) const
    {
        const int x_ = x * round(cos(rad)) - y * round(sin(rad));
        const int y_ = x * round(sin(rad)) + y * round(cos(rad));
        return PointInteger(x_, y_);
    }
    
    bool operator ==(const PointInteger& other) const
    {
        return (x == other.x && y == other.y) ? true : false;
    }

    // ��� ����������
    bool operator<(const PointInteger& other) const
    {
        return (x < other.x || (x == other.x && y < other.y));        
    }

    friend std::ostream& operator <<(std::ostream& out, const PointInteger& point) 
    {
        out << point.x << '\t' << point.y << '\n';
        return out;
    }
};

// ����� ������, ���� ������ �������� board
struct Board
{

    // ���������� ������
    std::vector<PointInteger> board;

    Board(){}

    Board(const int size)
    {
        for (int i = 0; i < size; ++i)
        {
            Push(PointInteger(0, 0));
        }
    }

    // ������ ���������� ������� ����� (������� ����� ������ ��� �� �������� ����)
    Board Rotate(const double rad) const
    {
        Board board_;
        for (auto a : board)
        {
            board_.Push(a.Rotate(rad));
        }
        return board_;
    }
        
    // ���������� �����
    void Push(const PointInteger& a)
    {
        board.push_back(a);
    }
    
    // �������� ��������� ��� 
    bool operator ==(const Board& other) const
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
    
    

    int MaxX() const
    {
        int max = -10000000;
        for (int i = 0; i < board.size(); ++i)
        {
            if (board[i].x > max)
            {
                max = board[i].x;
            }
        }
        return max;
    }

    int MinX() const
    {
        int max = 10000000;
        for (int i = 0; i < board.size(); ++i)
        {
            if (board[i].x < max)
            {
                max = board[i].x;
            }
        }
        return max;
    }
    
    int MaxY() const
    {
        int max = -10000000;
        for (int i = 0; i < board.size(); ++i)
        {
            if (board[i].y > max)
            {
                max = board[i].y;
            }
        }
        return max;
    }

    int MinY() const
    {
        int max = 10000000;
        for (int i = 0; i < board.size(); ++i)
        {
            if (board[i].y < max)
            {
                max = board[i].y;
            }
        }
        return max;
    }

    void Print(std::ostream& out) const
    {
        std::string print;
        const int sizeX = MaxX() - MinX() + 1;
        const int sizeY = MaxY() - MinY() + 1;
        for (int k = sizeY; k > 0; k--)
        {
            print.push_back(static_cast<char>(k + 48));
            for (int h = 0; h < sizeX; ++h)
            {
                if ((k + h) % 2 == 0)
                {
                    print.push_back('*');
                }
                else
                {
                    print.push_back(' ');
                }
            }
            print.push_back('\n');
        }
        print.push_back(' ');
        for (int h = 0; h < sizeX; ++h)
        {
            print.push_back(static_cast<char>(97 + h));
        }
        print.push_back('\n');

        for (int i = 0; i < board.size(); ++i)
        {
            print[board[i].y * (sizeX + 2) + board[i].x + 1] = 'Q';
        }

        out << print;
    }

    friend std::ostream& operator <<(std::ostream& out, const Board& boards)
    {
        std::string print;
        const int sizeX = boards.MaxX() - boards.MinX() + 1;
        const int sizeY = boards.MaxY() - boards.MinY() + 1;
        for (int k = sizeY; k > 0; k--)
        {
            print.push_back(static_cast<char>(k + 48));
            for (int h = 0; h < sizeX; ++h)
            {
                if ((k + h) % 2 == 0)
                {
                    print.push_back('*');
                }
                else
                {
                    print.push_back(' ');
                }
            }
            print.push_back('\n');
        }
        print.push_back(' ');
        for (int h = 0; h < sizeX; ++h)
        {
            print.push_back(static_cast<char>(97 + h));
        }
        print.push_back('\n');

        for (int i = 0; i < boards.board.size(); ++i)
        {
            print[boards.board[i].y * (sizeX + 2) + boards.board[i].x + 1] = 'Q';
        }

        out << print;
        return out;
    }
    
    // ������ ���� ������� ������ ������� �� ����� ������� 90 ��������
    bool IsRotate(Board  board90) const
    {   
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
//        std::cout << "������: " << row << "; C������: " << column << "\n";
}

// ������ ������ �����
void InputSizeBoard(int& limit)
{
    Input(limit, "������� ������ ����� ");
    limit = limit - 1;
}



/* ��� ��������� ������� ��� ������� ������ � ������ ������. */
int main() 
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    // �������� ����� �����
    std::ofstream out;
    std::string pathFileOutput;
    std::cout << "OutputFile\n";
    std::cin >> pathFileOutput;
    out.open(pathFileOutput);
    

    int limit = 4;
    InputSizeBoard(limit);
    Board board = Board(limit + 1);
    std::vector<Board> boards;
    std::vector<Board> noRotationBoard;


    int count = 0;
    Queen* pLastQueen = NULL;
    for (int i = 0; i <= limit; i++) 
    {
        // ������� � ���������������� ������ ����� � i-� �������
        pLastQueen = new Queen(i, pLastQueen);        
        if (!pLastQueen->FindSolution(limit))
            std::cout << "��� �������.\n";
    }
 
    // ����� �������
    do
    {
//        pLastQueen->Print(std::cout, count, limit);
        boards.push_back(board);
        pLastQueen->Boards(boards[count], 0);
        ++count;
    } while (pLastQueen->Advance(limit));
 
    
   
    for (int i = 0; i < boards.size(); ++i)
    {
        std::cout << "������� " << i << '\n' << '\n';
        out << "������� " << i << '\n' << '\n';
        std::cout << boards[i] << '\n';
        out << boards[i] << '\n';
    }
    
    // ����� ������� ��� ���������
    noRotationBoard.push_back(boards[0]);
    std::vector<Board> boardNoRotate;
    boardNoRotate.push_back(boards[0]);
    count = 0;
    for (int i = 1; i < boards.size(); ++i)
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
            boardNoRotate.push_back(boards[i]);
        }
    }
    

    for (int k = 0; k < boardNoRotate.size(); ++k)
    {
        std::cout << "������� ��� ��������� " << k << '\n' << '\n';
        out << "������� ��� ��������� " << k << '\n' << '\n';
        std::cout << boardNoRotate[k] << '\n';
        out << boardNoRotate[k] << '\n';
    }
    
    out.close();
    
    // �������� ��������-������
    while (pLastQueen) 
    {
        Queen* pPrevQueen = pLastQueen->GetNeighbor();
        delete pLastQueen;
        pLastQueen = pPrevQueen;
    }
    
    

    return 0;
}

