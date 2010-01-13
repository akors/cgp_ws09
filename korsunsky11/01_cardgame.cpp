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

    // create list of cards
    std::list<Card> cards;

    for (unsigned i = 0; i < 6; ++i )
        cards.push_back(Card());

    // print out the list
    std::copy(
        cards.begin(),
        cards.end(),
        std::ostream_iterator<Card>(std::cout, ", ")
    );

    std::cout<<std::endl;

    return 0;
}