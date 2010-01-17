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

    spiel.play();

    return 0;
}