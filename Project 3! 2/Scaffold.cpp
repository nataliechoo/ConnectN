// Scaffold.cpp

#include "provided.h"
#include <utility>
#include <vector>
#include <iostream>
#include <stack>
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
    
private:
    int mCols;
    int mLevels;
    vector<vector<char>> grid;
    stack<int> moves;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if (nColumns <= 0 || nLevels <= 0)
    {
        cerr << "invalid parameters" << endl;
        exit(1);
    }
    
    mCols = nColumns;
    mLevels = nLevels;

    grid.resize(nLevels);  // grid now has M empty rows
    for (int i = 0; i < nLevels; i++)
        grid.at(i).resize(nColumns);  // row i now has N columns
    
    for (int i = 0; i < nLevels; i++)
        //fill it up with empty space since it should be blank
    {
        for (int j = 0; j < nColumns; j++)
            grid.at(i).at(j) = ' ';
    }

}

int ScaffoldImpl::cols() const
{
    return mCols;
}

int ScaffoldImpl::levels() const
{
    return mLevels;
}

int ScaffoldImpl::numberEmpty() const       //check this for bugs
{
    //create a count for the amount of empty spaces found
    int count = 0;

    for (int i = 0; i < mLevels; i++)
        for (int j = 0; j < mCols; j++)
            if (grid.at(i).at(j) == ' ')
                count++;    // add to count when an empty space is found

    return count;   //return the number of empties found
}



int ScaffoldImpl::checkerAt(int column, int level) const
{
    //return vacant if the columns or level is out of range
    if (column > mCols || column <= 0)
        return VACANT;
    if (level > mLevels || level <= 0)
        return VACANT;
    
    //if the parameters are valid, look at the spot in the grid and return what is seen
    if (grid[level-1][column - 1] == 'R')
        return RED;
    if (grid[level-1][column-1] == 'B')
        return BLACK;
    else
        return VACANT;
}

void ScaffoldImpl::display() const
{
    //print each element of the grid according to its definition frm checkerAt
    for (int i = mLevels; i >=1; i--)
    {
        cout << '|';
        for (int j = 1; j <= mCols; j++)
        {
            if (checkerAt(j, i) == VACANT)
                cout << ' ';
            if (checkerAt(j, i) == RED)
                cout << 'R';
            if (checkerAt(j, i) == BLACK)
                cout << 'B';
 
            cout << '|';
        }
        cout << endl;
    }
    //at the bottom row after the content of the grid, print out + and - accordingly
    for (int i = 1; i <= 2*mCols+1; i++)
    {
        if (i % 2 != 0)
        {
            cout << '+';
        }
        if (i % 2 == 0)
        {
            cout << '-';
        }
    }
}


bool ScaffoldImpl::makeMove(int column, int color)
{
    //if it is a valid move...
    if (column >= 1 && column <= mCols && (color == RED || color == BLACK))
    {
        for (int i = 0; i < mLevels; i++)
        {
            //and if the spot is empty...
            if (checkerAt(column, i+1) == VACANT)
            {
                //depending on the color, put the appropriate marker in that slot
                if (color == RED)
                {
                    grid[i][column-1] = 'R';
                    moves.push(column);
                }
                else if (color == BLACK)
                {
                    grid[i][column-1] = 'B';
                    moves.push(column);
                }
                //once the move is made, return true
                return true;
            }
        }
    }
    //if it has not returned already by now, it is invalid so return false and do nothing
    return false;

}

int ScaffoldImpl::undoMove()
{
    //if our move stack is empty, there is nothing to undo
    if (moves.empty() == true)
        return 0;
    else
    {
        //otherwise, look at the last column
        int lastCol = moves.top();
        
        for (int j = mLevels; j >= 1; j--)
        {
            if (checkerAt(lastCol, j) == RED || checkerAt(lastCol, j) == BLACK)
            {
                //find the top element at this column, this is the last move made. replace it with an empty marker
                grid.at(j-1).at(lastCol-1) = ' ';
                moves.pop();
                
                //return the column of the undone move
                return lastCol;
            }
        }
    }
 //   otherwise, return 0
    return 0;
}

        


//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
