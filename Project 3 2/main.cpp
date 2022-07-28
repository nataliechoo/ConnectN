// main.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
   /* Scaffold m(4,3);
    m.display();
    cout << endl;
    m.makeMove(1,RED);
    m.makeMove(1,BLACK);
    m.makeMove(1,BLACK);
    m.makeMove(2,RED);
    m.makeMove(2,BLACK);
    m.makeMove(2,BLACK);
    m.makeMove(3,RED);
    m.makeMove(3,RED);
    m.makeMove(3,BLACK);
    m.makeMove(4,RED);
    
    
    m.display();
    
    cout << m.checkerAt(1,1) << endl;
    assert(m.checkerAt(1, 1) == RED);
    assert(m.checkerAt(2,3) == BLACK);
    assert(m.checkerAt(1,3) == BLACK);
    assert(m.checkerAt(1,2) == BLACK);
    assert(m.checkerAt(2,2) == BLACK);
    assert(m.checkerAt(2,1) == RED);  // WHY DOES IT THINK 2,1 IS BLACK */
    
    

  /*  cout << endl;
    for (int i = 0; i <= 10; i++)
    {
        cout << endl;
        m.undoMove();
        m.display();

    }
    m.undoMove();
    cout<< endl;
    m.display(); */
//    assert(!m.makeMove(0,RED));
//    assert(!m.makeMove(2,RED));
    cout << "enter dimension 1: ";
    int dim1;
    cin >> dim1;
    cout << "enter dimension 2: ";
    int dim2;
    cin >> dim2;
    cout << "enter goal: ";
    int N;
    cin >> N;
    
    
    cout << "two smart bots? (y/n): ";
    char bots;
    cin >> bots;
    if (bots == 'y')
    {
        SmartPlayer a("hi");
        SmartPlayer b("bye");
        Game g(dim1,dim2, N, &a, &b);
        g.play();
        cout << endl;
        
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
            cout << endl;
        }
        else
        {
            HumanPlayer a("hi");
            SmartPlayer b("bye");
            Game g(dim1,dim2, N, &a, &b);
            g.play();
            cout << endl;
        }
    }



    /*
  //  m.display();
    cout << endl;
    string name;
    cout << "What's your name?  ";
    getline(cin, name);
    //HumanPlayer hp(name);
   // SmartPlayer sp("Computer");
    Game g1(4, 3, 3, &hp, &sp);
    g1.play();
    cout << endl << "This time I'll go first." << endl;
    Game g2(4, 3, 3, &sp, &hp);
    g2.play();
     */
}
