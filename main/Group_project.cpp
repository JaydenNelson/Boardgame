/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 /*
  * File:   main.cpp
  * Author: MSCS
  *
  * Created on 12 March 2020, 8:38 AM
  */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include "board.h"
#include "agent.h"


using namespace std;

int main(int argc, char** argv) {
    int i = 0;
    time_t now = time(NULL);                                //
    srand(now);                                            // used for the seed so that no 2 games are the same 
    cout << "Seed: " << now << endl;
    board abalone;
    string state(abalone);
    cout << "Initial State:" << endl << state;
    agent* w = new distAgent('O');              // ------------------------------------------------------randAgent always looses
    agent* b = new distAgent('@');
    movement* pom = nullptr;//previous opponent's move
    movement* mym = nullptr;//player's chosen move

    
    char c = '@';
    ofstream Log("savedMoves.txt");
   // for (int i = 0;i < 20;i++) 
    while(abalone.inPlay())
    {
        if (abalone.inPlay()) { //--------------------------------------------------------------------------------- checks for a winner 


            try {
                if (c == 'O') {
                    movement mm = w->move(pom, abalone);
                    mym = new movement(mm);
                    if (pom)
                        delete pom;
                    pom = new movement(mm);
                }
                else {
                    movement mm = b->move(pom, abalone);
                    mym = new movement(mm);
                    if (pom)
                        delete pom;
                    pom = new movement(mm);
                }
            }
            catch (const string& s) {
                cout << s;
                return 1;
            }
            bool valid = abalone.executeMove(c, mym->l, mym->n, mym->fd, mym->md);
            cout << "Move " << i + 1 << ": " << c << "," << mym->l << "," << mym->n << "," << mym->fd << "," << mym->md << endl;

            //----------------------------
           // ofstream Log("savedMoves.txt");
              
           Log << "Move " << i + 1 << ": " << c << "," << mym->l << "," << mym->n << "," << mym->fd << "," << mym->md << endl;

           //Log.close();


            //--------------------------------
            if (valid) {
                string state(abalone);
                cout << "Next State:" << endl << state;
            }
            else {
                cout << "Invalid move!!" << endl;
            }
            if (c == 'O')
                c = '@';
            else
                c = 'O';
            delete mym;
            //SLP(1); //----------------------------------------------------------------------------slows down game 
        }
       /* else {
            cout << "game over" << endl;
            break;
        }*/
        //system(CL);
        i++;
    }
    cout << "game over" << endl;
    Log.close();

    if (pom)
        delete pom;
    delete w;
    delete b;

    return 0;
}

/*Notes 

Saving :

save the moves up until a save prompt is given , then when loading the game let it read from the text file and automatically play the game till that point




*/