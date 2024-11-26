/*
GridSolver by Kacpron
using wikipedia methods:
https://en.wikipedia.org/wiki/Nonogram#Simple_spaces
*/

#include "Puzzledata.h"
#include <iostream>

struct nextsolve{
    int x;
    int y;
    dimension dim;
};
int main(){
    Puzzledata puzzle(246148);
    puzzle.Solve();
    puzzle.Print();
    std::cout<<std::endl;
    return 0;
}
