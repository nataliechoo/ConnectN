// main.cpp
#include "provided.h"
#include <iostream>
#include <cassert>
using namespace std;



int main()
{
    cout << "enter dimension 1 (width): ";
    int dim1;
    cin >> dim1;
    cout << "enter dimension 2 (height): ";
    int dim2;
    cin >> dim2;
    cout << "enter goal: ";
    int N;
    cin >> N;
    
    cout << "you vs badplayer? (y/n): ";
    char badplayer;
    cin >> badplayer;
    if (badplayer == 'y')
    {
        cout << "human first? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y')
        {
            HumanPlayer a("hi");
            BadPlayer b("bye");
            Game g(dim1,dim2, N, &a, &b);
            g.play();
            return 0;
        }
        else
        {
            BadPlayer a("hi");
            HumanPlayer b("bye");
            Game g(dim1,dim2, N, &a, &b);
            g.play();
            return 0;
        }
    }
    cout << "two smart bots? (y/n): ";
    char bots;
    cin >> bots;
    if (bots == 'y')
    {
        SmartPlayer a("hi");
        SmartPlayer b("bye");
        Game g(dim1,dim2, N, &a, &b);
        g.play();
        return 0;
    }
    else
    {
        cout << "Smart player first? (y/n): ";
        char i;
        cin >> i;
        if (i == 'y')
        {
            SmartPlayer a("hi");
            HumanPlayer b("bye");
            Game g(dim1,dim2, N, &a, &b);
            g.play();
            return 0;
        }
        else
        {
            HumanPlayer a("hi");
            SmartPlayer b("bye");
            Game g(dim1,dim2, N, &a, &b);
            g.play();
            return 0;
        }
    }
    return 0;
}
