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
    
    int findWinner(Scaffold s, int N, int lastCol);
    int minimax(Scaffold& s, int color, int N, int depth, int lastCol);
    mInfo determineBestMove(Scaffold &s, int color, int N);

};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    for (int i = 1; i <= s.cols(); i++)
    {
        if (s.checkerAt(i, s.levels()) == VACANT)
        {
            cout << endl;
            cout << "provide a move: ";
            int move = -1;
            cin >> move;
            while (move <= 0 || move > s.cols())
            {
                cout << "provide a VALID move: ";
                cin >> move;
            }
            while (move >= 1 && move <= s.cols())
            {
                if (s.checkerAt(move, s.levels()) != VACANT)
                {
                    cout << "choose am open column!" << endl;
                    cin >> move;
                    while (s.checkerAt(move, s.levels()) != VACANT)
                    {
                        cout << "please pick a valid column! ";
                        cin >> move;
                    }
                }
                else
                    break;
            }
            cin.ignore(1000, '\n');
            return(move);
        }
    }
    return (0); //no possible moves
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)   // if its a finished game, return 0 to indicate no possible moves
        return 0;
    
    for (int i = 1; i <= s.cols(); i++) // make a move in whichever available column you find first when searching from left to right
    {
        if (s.checkerAt(i, s.levels()) == VACANT)
            return i;
    }
    
    return 0;
}


int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    Scaffold copy = s;  //copy the scaffold so that it can remain const
    
    mInfo best = determineBestMove(copy, color, N);     //find best move
        
    return best.move;       //return the best move
}


int SmartPlayerImpl::findWinner(Scaffold s, int N, int lastCol)
{
    int reds = 0;
    int black = 0;

    //check columns for win pattern
    for (int j = 1; j <= s.cols(); j++)
    {
        //reset counts for each column
        reds = 0;
        black = 0;
        
        for (int i = 1; i <= s.levels(); i++)
            //increase count whenever one color is found, decrease count of opposing color when the main color is found, decrease both counts when an empty spot is found
        {
            if (s.checkerAt(j, i) == VACANT)
            {
                if (reds != 0)  {reds--;}
                if (black != 0) {black--;}
            }
            else if (s.checkerAt(j, i) == RED)
            {
                reds++;
                if (black != 0) {black--;}
            }
            else if (s.checkerAt(j, i) == BLACK)
            {
                black++;
                if (reds != 0)  {reds--;}
            }
            
            // if our counts are correct, return appropiate winners
            if (reds == N)
                return (RED);
            else if (black == N)
                return (BLACK);
        }
    }
    
    
    for (int i = 1; i <= s.levels(); i++)   //check every row for a winning pattern
    //increase count whenever one color is found, decrease count of opposing color when the main color is found, decrease both counts when an empty spot is found
    {
        //each row should start with counts of 0
        reds = 0;
        black = 0;
        
        for (int j = 1; j <= s.cols(); j++)
        {
            if (s.checkerAt(j, i) == VACANT)
            {
                if (reds != 0)  {reds--;}
                if (black != 0) {black--;}
            }
            else if (s.checkerAt(j, i) == RED)
            {
                reds++;
                if (black != 0) {black--;}
            }
            else if (s.checkerAt(j, i) == BLACK)
            {
                black++;
                if (reds != 0)  {reds--;}
            }
            
            // if our counts are correct, return appropiate winners
            if (reds == N)
                return (RED);
            else if (black == N)
                return (BLACK);
        }
    }
    
    //find a diagonal win pattern of the arrangement: y = -x

    for (int maxlevel = 1; maxlevel <= s.levels(); maxlevel++)
       {
           // if either of these are true, there will be no winner
           if (s.cols() < N)
               break;
           if (s.levels() < N)
               break;

           for (int k = maxlevel; k <= s.cols(); k++)
               // so that we do not go out of bounds
           {
               reds = 0;
               black = 0;
               int i = maxlevel;
               for (int j = k; j <= s.cols(); j++)      // check from left to right
               {
                   if (s.checkerAt(j, i) == VACANT)
                   {
                       if (reds != 0)   {reds--;}
                       if (black != 0)  {black--;}
                   }
                   if (s.checkerAt(j, i) == RED)
                   {
                       reds++;
                       if (black != 0)  {black--;}
                   }
                   else if (s.checkerAt(j, i) == BLACK)
                   {
                       black++;
                       if (reds != 0)   {reds--;}
                   }
                   
                   if (black == N)  {return(BLACK);}
                   if (reds == N)   {return(RED);}
                   
                   if (i == s.levels()) // we are at the max level, stop checking so we dont go out of bounds
                   {
                       i = maxlevel;
                       break;
                   }
                   else if (i < s.levels()) // keep going up while we can
                       i++;
                       
               }
           }
       }
    
    //  find diagonal win pattern of the arrangement:  y = x
       for (int maxlevel = 1; maxlevel <= s.levels(); maxlevel++)
       {
           //impossible to win if these are true
           if (s.cols() < N)
               break;
           if (s.levels() < N)
               break;

           for (int k = s.cols(); k >= 1; k--)  // search from right to left
           {
               reds = 0;
               black = 0;
               int i = maxlevel;
               for (int j = k; j >= 1; j--)
               {
                   if (s.checkerAt(j, i) == RED)
                   {
                       reds++;
                       if (black != 0)
                           black--;
                   }
                   else if (s.checkerAt(j, i) == BLACK)
                   {
                       black++;
                       if (reds != 0)
                           reds--;
                   }
                   else if (s.checkerAt(j, i) == VACANT)
                   {
                       if (reds != 0)
                           reds--;
                       if (black != 0)
                           black--;
                   }
                   if (reds == N)
                   {
                       return(RED);
                   }
                   if (black == N)
                   {
                       return(BLACK);
                   }
                   if (i < s.levels())
                       i++;
                   else if (i == s.levels())
                   {
                       i = maxlevel;
                       break;
                   }
                       
               }
           }
       }
    
    if (s.numberEmpty() == 0)
        return TIE_GAME;
    else
        return 3333;
    
}


int SmartPlayerImpl::minimax(Scaffold& s, int color, int N, int depth, int lastCol)
//finds the best possible outcome given a scaffold for the given color
{
    int victor = findWinner(s, N, lastCol);
    
    //BASE CASE: determine final game state
    if (victor != 3333) //if the game is in a completed state
    {
        if (victor == BLACK) {  return (-1 * (2000 - depth));   }           //farther losses are ideal
        else if (victor == RED) {    return (2000 - depth);  }              // further wins are less desirable than more immediate wins
        else if (victor == TIE_GAME) {  return depth;   }                   //farther ties are ideal
        
    }
    
    int idealScore;
    //test each possible move made and find its rating... return the ideal score according to the color of the player
    if (color == BLACK)
    {
        idealScore = 2000;  //initializer that would not be chosen bc of max
        
        for (int i = 1; i <= s.cols(); i++)
        {
            bool moveMade = s.makeMove(i, BLACK); // make the experimental move

            if (moveMade) // if we can make a move here...
            {
                //update our ideal score

                idealScore = min(idealScore, minimax(s, RED, N, depth+1, i)); // find the best move for a BLACK player by MINIMIZING
                s.undoMove(); // return scaffold to original state
            }
            // if moveMade is false, nothing was done to the scaffold so there is no need to undo...
        }
        return (idealScore);
        //after trying every move, return the best one
    }
    else    //do the same thing but for RED
    {
        idealScore = -2000;  //initializer that will not be chosen bc of min
        for (int i = 1; i <= s.cols(); i++)
        {
            bool moveMade = s.makeMove(i, RED); // make the experimental move

            if (moveMade) // if we can make a move here...
            {
                //update our ideal score
                
                idealScore = max(idealScore, minimax(s, BLACK, N, depth+1, i)); // find the best move for a RED player by MAXIMIZING!
                s.undoMove(); // return scaffold to original state
            }
            // if moveMade is false, nothing was done to the scaffold so there is no need to undo...
        }
        return(idealScore); //after trying every move, return the best one
    }
        
}

SmartPlayerImpl::mInfo SmartPlayerImpl::determineBestMove(Scaffold &s, int color, int N)
{
    mInfo best; // this will be a container for our best move and its corresponding score
    
    //initialize best score so that it wont be chosen by our function
    if (color == BLACK) {best.score = 2000;}
    else if (color == RED) {best.score = -2000;}
    
    mInfo current;  // this will be a container for the current move under assessment
    
    for (int i = 1; i <= s.cols(); i++)
    {
        if (color == RED)
        {
            //make a red move
            bool moveMade = s.makeMove(i, RED);
            
            if (moveMade)   // if the move is valid
            {
                //update our current variable
                current.score = minimax(s, BLACK, N, 0, i);
                current.move = i;
                
                //update our best move if the current one being assessed is greater
                if (current.score >= best.score)    // the best is the maximum
                {
                    best.move = current.move;
                    best.score = current.score;
                }
                s.undoMove();   //return the scaffold to original state
            }
        }
        else if (color == BLACK)
        {
            //make a black move
            bool moveMade = s.makeMove(i, BLACK);
            
            if (moveMade)   // if the mvoe is valid
            {
                //update our current variable
                current.score = minimax(s, RED, N, 0, i);
                current.move = i;
                
                //update our best variable to the current one if it is more ideal
                if (current.score <= best.score)    // the best is now the minimum
                {
                    best.move = current.move;
                    best.score = current.score;
                }
                s.undoMove();
            }
        }
    }
    return best;
    //depending on the color, best will either return the highest score and its appropiate move, or the lowest score and its appropriate move
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
