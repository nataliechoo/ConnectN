// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;


class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
private:
    
    struct mInfo
    {
        int move;
        int score;
    };
    
    int rating(Scaffold s, int last, int color, int goal, int depth);
    
    mInfo determineBestComputerMove(Scaffold s, int depth, int color, int N, vector<mInfo>& scores);
    mInfo determineBestHumanMove(Scaffold s, int depth, int color, int N, vector<mInfo>& scores);
    bool least(mInfo a, mInfo b) const;

    bool greater(mInfo a, mInfo b) const;

    vector<mInfo> mScores;
    
    //since im passing vectors in by reference so that i can save the results to an existing vector, should i have two separate vectors? one for computer moves, and another for human simulated moves?
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    cout << endl;
    cout << "provide a move: ";
    int move = -1;
    cin >> move;
    while (move < 1 || move > s.cols())
    {
        cout << "provide a VALID move: ";
        cin >> move;
    }
        
    return move;  
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
//always put check in left most row
{
    if (s.numberEmpty() == 0)
        return 0;
    
    for (int i = 1; i <= s.cols(); i++)
    {
        if (s.checkerAt(i, s.levels()) == VACANT)
            return i;
    }
    
    return 0;  //  This is not always correct; it's just here to compile
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    mInfo best = determineBestComputerMove(s, 0, color, N, mScores);
    
    mScores.resize(0);
    
    return best.move;
}

SmartPlayerImpl::mInfo SmartPlayerImpl::determineBestComputerMove(Scaffold s, int depth, int color, int N, vector<mInfo>& scores)
{
  //  scores.resize(0);

    for (int i = 1; i <= s.cols(); i++)
        //check each possible move, rate them, and store them into the scores vector if it is a win or tie
    {
     //   cout << endl << scores.size() << endl;
        bool moveMade = s.makeMove(i, color);
        if (moveMade == true)
        {
            int lastScore = rating(s, i, color, N, depth);
            if (lastScore >=0 && lastScore != 3333)
                //if this move gives us a win or tie, store the move and the score
            {
                mInfo move;
                move.score = lastScore;
                move.move = i;
                scores.push_back(move);
            }
            else
                //if this move doesnt end the game, have the opponent go and store the value
            {
                scores.push_back(determineBestHumanMove(s, depth + 1, (1 - color), N, scores));
            }
            s.undoMove();
        }
    }
        
    //instead, a made a struct that holds the rating, depth, and column
  
    mInfo best = scores.front();
        
    for (int i = 0; i < scores.size(); i++)
        // find the best score out of all the stored ones
    {
       if (greater(scores[i], best))
           best = scores[i];
    }
    
 /*   for (int i = 0; i < scores.size(); i++)
        cout << scores[i].move << " " << scores[i].score << endl; */
    
 //   scores.resize(0);
    
    return best;
    
}

bool SmartPlayerImpl::greater(mInfo a, mInfo b) const
{
    if (a.score > b.score)
        return true;
    else
        return false;
}
bool SmartPlayerImpl::least(mInfo a, mInfo b) const
{
    if (a.score < b.score)
        return true;
    else
        return false;
}

SmartPlayerImpl::mInfo SmartPlayerImpl::determineBestHumanMove(Scaffold s, int depth, int color, int N, vector<mInfo>& scores)
{
    for (int i = 1; i <= s.cols(); i++)
        //check each possible move, rate them, and store them into the scores vector if it is a win or tie
    {
        bool moveMade = s.makeMove(i, color);

        if (moveMade == true)
        {
            int lastScore = -(rating(s, i, color, N, depth));
            if (lastScore <=0 && lastScore != -3333)
                //if this move gives us a win or tie, store the move and the score
            {
                mInfo move;
                move.score = lastScore;
                move.move = i;
                scores.push_back(move);
            }
            else
                //if this move doesnt end the game, have the opponent go and store the value
            {
                scores.push_back(determineBestComputerMove(s, depth + 1, (1 - color), N, scores));
            }
            s.undoMove();

        }
    }
    //instead, a made a struct that holds the rating, depth, and column
  
    mInfo lowest = scores.front();
        
    for (int i = 0; i < scores.size(); i++)
        // find the best score out of all the stored ones
    {
       if (least(scores[i], lowest))
           lowest = scores[i];
    }
   
    /*for (int i = 0; i < scores.size(); i++)
        cout << scores[i].move << " " << scores[i].score << endl; */
   // scores.resize(0);
    
    return lowest;
    
    //The function then returns two numbers: (a) one indicating which move should be made on behalf of the computer (and the makeComputerMove function can then make that move), and (b) a number (1, 0, or −1) that indicates the best possible score that the suggested move will eventually result in.
    //HOW DO I RETURN THE SECOND VALUE
}

int SmartPlayerImpl::rating(Scaffold s, int last, int color, int goal, int depth)
{
    //find the level of lastMove
    int lastLev;
    for ( lastLev = s.levels(); lastLev >= 1; lastLev--)
    {
        if (s.checkerAt(last, lastLev) == color)    // this should find the top matching value in lastMove's column. now, lastLev will be updated to the right level
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
    for (int i = last - 1; i >= 1; i--)
        //i am checking all the items to the left of last move
    {
        if (s.checkerAt(i, lastLev) == color)
            counter++;
        else
            break;
        if (counter == goal)
        {
            return (100000 - depth);
        }
    }
    
    counter = 1;
    //checkign all items to the right
    for (int i = last + 1; i <= s.cols(); i++)
    {
        if (s.checkerAt(i, lastLev) == color)
            counter++;
        else
            break;
        if (counter == goal)
        {
            return (100000 - depth);
        }
        
    }
    
    counter = 0;
    //check all  left to right horizontally
    for (int i = 1; i <= s.cols(); i++)
    {
        if (s.checkerAt(i, lastLev) == color)
            counter++;
        else
            counter = 0;
        if (counter == goal)
        {
            return (100000 - depth);
        }
    }
    
    counter = 1;
    //checking down
    for (int i = lastLev - 1; i >=1; i--)
    {
        if (s.checkerAt(last, i) == color)
            counter++;
        else
            break;
        if (counter == goal)
        {
            return (100000 - depth);
        }
    }
    
    counter = 1;
    //checking upper right... return 1 if we find a win pattern
    int i = lastLev + 1;
    int j = last + 1;
    while (i <= s.levels() && j <= s.cols())
    {
        if (s.checkerAt(j, i) == color)
            counter++;
        else
            break;
        if (counter == goal)
        {
            return (100000 - depth);
        }
        i++;
        j++;
    }
    
    counter = 1;
    //checking upper left... return 1 if we find a win pattern
    i = lastLev + 1;
    j = last - 1;
    while (i <= s.levels() && j >=1)
    {
        if (s.checkerAt(j, i) == color)
            counter++;
        else
            break;
        if (counter == goal)
        {
            return (100000 - depth);
        }
        i++;
        j--;
    }
    
    counter = 1;
    //checking bottom right... return 1 if we find a win pattern
    i = lastLev - 1;
    j = last + 1;
    while (i >= 1 && j <= s.cols())
    {
        if (s.checkerAt(j, i) == color)
            counter++;
        else
            break;
        if (counter == goal)
        {
            return (100000 - depth);
        }
        i--;
        j++;
    }
    
    counter = 1;
    //checking bottom left... return 1 if we find a win pattern
    i = lastLev - 1;
    j = last - 1;
    while (i >= 1 && j >= 1)
    {
        if (s.checkerAt(j, i) == color)
            counter++;
        else
            break;
        if (counter == goal)
        {
            return (100000 - depth);
        }
        i--;
        j--;
    }
    
    counter = 0;
    //check all diagonally (y=x top right half)
    i = lastLev;
    j = last;
    while (i <= s.levels() && j >=1)
    {
        if (s.checkerAt(j, i) == color)
            counter++;
        else
            break;
        if (counter == goal)
        {
            return (100000 - depth);
        }
        i++;
        j++;
    }
    //check all diagonally (y=x bottom left half)
    i = lastLev-1;
    j = last-1;
    while (i >=1 && j >=1)
    {
        if (s.checkerAt(j, i) == color)
            counter++;
        else
            break;
        if (counter == goal)
        {
            return (100000 - depth);
        }
        i--;
        j--;
    }
    
    counter = 0;
    //check all diagonally (y=-x top left half)
    i = lastLev;
    j = last;
    while (i <= s.levels() && j >= 1)
    {
        if (s.checkerAt(j, i) == color)
            counter++;
        else
            break;
        if (counter == goal)
        {
            return (100000 - depth);
        }
        i++;
        j--;
    }
    //check all diagonally (y=-x bottom right half)
    i = lastLev-1;
    j = last +1;
    while (i >=1 && j >=1)
    {
        if (s.checkerAt(j, i) == color)
            counter++;
        else
            break;
        if (counter == goal)
        {
            return (100000 - depth);
        }
        i--;
        j++;
    }

    if (s.numberEmpty() == 0)
        //this results in a tie, return 0
    {
        return 0;
    }
    
    return 3333;    //indicates an unfinished game
}
//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
