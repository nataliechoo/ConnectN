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
    {
        for (int j = 0; j < nColumns; j++)
            grid.at(i).at(j) = ' ';
    }
    grid[0][0] = '3';

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
    int count = 0;

    for (int i = 0; i < mLevels; i++)
        for (int j = 0; j < mCols; j++)
            if (grid.at(i).at(j) != 'R' && grid.at(i).at(j) != 'B' && grid.at(i).at(j) == ' ')
                count++;

    return count;
}



int ScaffoldImpl::checkerAt(int column, int level) const
{
    //im so confused i think i just overcomplicated it it is 4am so im going to go to sleep
    
    //problem summary:
    // I realized that level was not being checked correctly. from what i know, the 2d vector sees the grid from 0 (top level ) to mLevel-1 (bottom level), but the level system of the game is 1 (bottom) to mLevel (top).. because of this, checkerAt is not correctly checking values at the top and bottom levels checkerAt(1,3) will look at position (1,1) and checkerAt(1,1) will look at position (1,3)
    
    //i did the giant chunk with a mini equation that should give the right translated index but i havent adjusted my other functions to work with it, so it doesnt run properly anymore... i dont think this function should be this complicated so im gonna get help in the morning
    
    if (column > mCols || column <= 0)
        return VACANT;
    if (level > mLevels || level <= 0)
        return VACANT;
    
    /*
    if (mLevels % 2 == 0)
    {
        if (level > (mLevels/2))
        {
            if (grid.at(level-(mLevels - 2 * (mLevels - level))).at(column-1) == 'R')
                return RED;
            if (grid.at(level-(mLevels - 2 * (mLevels - level))).at(column-1) == 'B')
                return BLACK;
            else
                return VACANT;
        }
        if (level < (mLevels/2))
        {
            if (grid.at(level + ((mLevels - 2)/level)).at(column-1) == 'R')
                return RED;
            if (grid.at(level + ((mLevels - 2)/level)).at(column-1) == 'B')
                return BLACK;
            else
                return VACANT;
        }
        if (level == mLevels)
        {
            if (grid.at(0).at(column-1) == 'R')
                return RED;
            if (grid.at(0).at(column-1) == 'B')
                return BLACK;
            else
                return VACANT;
        }
        if (level == (mLevels/2))
        {
            if (grid.at(level).at(column-1) == 'R')
                return RED;
            if (grid.at(level).at(column-1) == 'B')
                return BLACK;
            else
                return VACANT;
        }
    }
    else
    {
        if (level == mLevels)
        {
            if (grid.at(0).at(column-1) == 'R')
                return RED;
            if (grid.at(0).at(column-1) == 'B')
                return BLACK;
            else
                return VACANT;
        }
        if (level > (mLevels/2))
        {
            if (grid.at(level-(mLevels - 2 * (mLevels - level))).at(column-1) == 'R')
                return RED;
            if (grid.at(level-(mLevels - 2 * (mLevels - level))).at(column-1) == 'B')
                return BLACK;
            else
                return VACANT;
        }
        if (level <= (mLevels/2))
        {
            if (grid.at(level + ((mLevels - 2)/level)).at(column-1) == 'R')
                return RED;
            if (grid.at(level + ((mLevels - 2)/level)).at(column-1) == 'B')
                return BLACK;
            else
                return VACANT;
        }
    }
    
        return VACANT; //just to compile.. DOUBLE CHECK TO MAKE SURE I GOT ALL CASES
    */
    //this needs to be fixed... currently with a level size of 3, 3 refers to the bottom and 1 refers to the top
    if (grid[level-1][column - 1] == 'R')
        return RED;
    if (grid[level-1][column-1] == 'B')
        return BLACK;
    else
        return VACANT;
}

void ScaffoldImpl::display() const
{
    
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
  /*  if (checkerAt(column, levels()) == RED ||checkerAt(column, levels()) == BLACK)
        return false; */
    if (column >= 1 && column <= mCols && (color == RED || color == BLACK))
    {
        for (int i = 0; i < mLevels; i++)
        {
            if (checkerAt(column, i+1) == VACANT)
            {
                if (color == RED)
                {
                    grid[i][column-1] = 'R';
                    moves.push(column);
                }
                else
                {
                    grid[i][column-1] = 'B';
                    moves.push(column);
                }
                return true;
            }
        }
    }
    return false;

}

int ScaffoldImpl::undoMove()
{
    if (moves.empty() == true)
        return 0;
    else
    {
        int lastCol = moves.top();
        
        for (int j = 0; j <= mLevels; j++)
        {
            if (checkerAt(lastCol, j+1) == RED || checkerAt(lastCol, j+1) == BLACK)
            {
                grid.at(j).at(lastCol-1) = ' ';
                moves.pop();
                return lastCol;
            }
        }
    }
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
