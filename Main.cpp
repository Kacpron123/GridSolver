/*
GridSolver by Kacpron
using wikipedia methods:
https://en.wikipedia.org/wiki/Nonogram#Simple_spaces
*/

#include "Puzzledata.h"
#include <iostream>
#include <string>

struct nextsolve{
    int x;
    int y;
    dimension dim;
};
int main(int argc, char* argv[]){
    if(argc!=2)
        throw std::logic_error("not added id of puzzle");
    Puzzledata puzzle(std::stoi(argv[1]));
    puzzle.Solve();
    puzzle.Print(true);
    std::cout<<std::endl;
    return 0;
}
