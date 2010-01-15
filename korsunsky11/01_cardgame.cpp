#include <iostream>
#include <list>
#include <iterator>

#include <cstdlib>
#include <ctime>

#include "game.hpp"

int main()
{
    // Ininitalize stdlib randon number generator
    srand(time(NULL));


    Talon spiel(6);

    std::cout<<"\nvorher: \n";
    spiel.showCards();

    spiel.removePair(5);
    spiel.removePair(2);
    std::cout<<'\n';

    std::cout<<"\nnachher: \n";
    spiel.showCards();

    return 0;
}