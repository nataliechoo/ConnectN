// Game.cpp

#include "provided.h"
#include <iostream>
#include <stack>


class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
    
private:
    Scaffold s;
    int goal;
    Player*  red1;
    Player* black2;
    int lastMove;
    int whoWon;
    std::stack<int> turns;
    int lastValue;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black) : s(nColumns, nLevels), red1(red), black2(black)
{
    if (N <= 0)
//error msg???
        std::cout << "BAD!" << std::endl;
    else
        goal = N;
    
        //idk what it wants me to do for some of these
    //indicated players
    //on a scaffold of the right size, (done)
    //red goes first,
    //goal is to get N in a row (done??? maybe??)
}

bool GameImpl::completed(int& winner) const
{
    //find the level of lastMove
    int lastLev;
    for ( lastLev = s.levels(); lastLev >= 1; lastLev--)
    {
        if (s.checkerAt(lastMove, lastLev) == lastValue)    // this should find the top matching value in lastMove's column. now, lastLev will be updated to the right level
            break;
    }
    
    //check r to l
    //check down
    //check down left, down right
    //check up left, up right
    
    //if no match or out of bounds, exit loop
    
    //start with a count of 1, reset count with each new directional loop
        //within for loop: if reaches N matches, good
    

    int counter = 1;
    for (int i = lastMove - 1; i >= 1; i--)
        //i am checking all the items to the left of last move
    {
        if (s.checkerAt(i, lastLev) == lastValue)
            counter++;
        else
            break;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
    }
    
    counter = 1;
    //checkign all items to the right
    for (int i = lastMove + 1; i <= s.cols(); i++)
    {
        if (s.checkerAt(i, lastLev) == lastValue)
            counter++;
        else
            break;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
        
    }
    
    counter = 0;
    //check all  left to right horizontally
    for (int i = 1; i <= s.cols(); i++)
    {
        if (s.checkerAt(i, lastLev) == lastValue)
            counter++;
        else
            counter = 0;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
    }
    
    counter = 1;
    //checking down
    for (int i = lastLev - 1; i >=1; i--)
    {
        if (s.checkerAt(lastMove, i) == lastValue)
            counter++;
        else
            break;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
    }
    
    counter = 1;
    //checking upper right
    int i = lastLev + 1;
    int j = lastMove + 1;
    while (i <= s.levels() && j <= s.cols())
    {
        if (s.checkerAt(j, i) == lastValue)
            counter++;
        else
            break;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
        i++;
        j++;
    }
    
    counter = 1;
    //checking upper left
    i = lastLev + 1;
    j = lastMove - 1;
    while (i <= s.levels() && j >=1)
    {
        if (s.checkerAt(j, i) == lastValue)
            counter++;
        else
            break;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
        i++;
        j--;
    }
    
    counter = 1;
    //checking bottom right
    i = lastLev - 1;
    j = lastMove + 1;
    while (i >= 1 && j <= s.cols())
    {
        if (s.checkerAt(j, i) == lastValue)
            counter++;
        else
            break;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
        i--;
        j++;
    }
    
    counter = 1;
    //checking bottom left
    i = lastLev - 1;
    j = lastMove - 1;
    while (i >= 1 && j >= 1)
    {
        if (s.checkerAt(j, i) == lastValue)
            counter++;
        else
            break;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
        i--;
        j--;
    }
    
    counter = 0;
    //check all diagonally (y=x top right half)
    i = lastLev;
    j = lastMove;
    while (i <= s.levels() && j >=1)
    {
        if (s.checkerAt(j, i) == lastValue)
            counter++;
        else
            break;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
        i++;
        j++;
    }
    //check all diagonally (y=x bottom left half)
    i = lastLev-1;
    j = lastMove-1;
    while (i >=1 && j >=1)
    {
        if (s.checkerAt(j, i) == lastValue)
            counter++;
        else
            break;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
        i--;
        j--;
    }

    counter = 0;
    //check all diagonally (y=-x top left half)
    i = lastLev;
    j = lastMove;
    while (i <= s.levels() && j >= 1)
    {
        if (s.checkerAt(j, i) == lastValue)
            counter++;
        else
            break;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
        i++;
        j--;
    }
    //check all diagonally (y=-x bottom right half)
    i = lastLev-1;
    j = lastMove +1;
    while (i >=1 && j >=1)
    {
        if (s.checkerAt(j, i) == lastValue)
            counter++;
        else
            break;
        if (counter == goal)
        {
            winner = lastValue;
            return true;
        }
        i--;
        j++;
    }
    
    if (s.numberEmpty() == 0)
    {
        winner = TIE_GAME;
        return true;
    }
    
    return false;
}
//  This is not always correct; it's just here to compile


bool GameImpl::takeTurn()
{
    if (turns.empty() || turns.top() == BLACK)
        //we want red to go
    {
        if (completed(whoWon))
            return false;
        else
        {
            //store the last move and its color so that we can more efficiently solve completed()
            lastMove = red1->chooseMove(s, goal, RED);
            lastValue = RED;
            
            //make the move and store the last color so at the next turn, we will know which player is to go
            s.makeMove(lastMove, RED);
            turns.push(RED);
            return true;
        }
    }
    else
        //we want black to go
    {
        if (completed(whoWon))
            return false;
        else
        {
            //store the last move and its color so that we can more efficiently solve completed()
            lastMove = black2->chooseMove(s, goal, BLACK);
            lastValue = BLACK;
            
            //make the move and store the last color so at the next turn, we will know which player is to go
            s.makeMove(lastMove, BLACK);
            turns.push(BLACK);
            return true;
        }
    }

}

void GameImpl::play()
{
    if (red1->isInteractive() == false && black2->isInteractive() == false)
    {
        int i = 1;
        while (!completed(whoWon))
        {
            //while the game is still going, show the display and prompt for a turn
            s.display();
            std::cout << std::endl;
            takeTurn();
            std::cout << std::endl;
            std::string enter;

            //prompt for enter to continue
            do
            {
                std::cout << "press enter to continue... ";
                getline(std::cin, enter);
                if (i == 1)
                {
                    std::cout << std::endl;
                    i++;
                }
            } while (enter.length() != 0);
        }
       // std::cout << std::endl;
        s.display();
    }
    else
    {
        while (!completed(whoWon))
        {
            s.display();
            takeTurn();
            std::cout << std::endl;
        }
        s.display();
        
    }
    std::cout << std::endl;
    if (whoWon == RED)
        std::cout << "the winner is: RED!" << std::endl;
    else if (whoWon == BLACK)
        std::cout << "the winner is: BLACK!" << std::endl;
    else if (whoWon == TIE_GAME)
        std::cout << "TIE!" << std::endl;
}

int GameImpl::checkerAt(int c, int r) const
{
    return s.checkerAt(c, r);  //  This is not always correct; it's just here to compile
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
