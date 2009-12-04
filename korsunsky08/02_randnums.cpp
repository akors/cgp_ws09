#include <iostream>
#include "zufall.hpp"

typedef generic_C_zufall<double, 1283, 106, 6075> C_zufall;

void printRandNums(int seed)
{
    const unsigned num_nums = 10;

    C_zufall zzahl(seed);

    std::cout<<"10 Zufallszahlen (Seed = "<<seed<<"): \n";
    std::cout<<zzahl.Getrandom();
    for (unsigned i = 1; i < num_nums; ++i)
        std::cout<<", "<<zzahl.Getrandom();
    std::cout<<std::endl;
}

int main()
{
    printRandNums(0);
    printRandNums(5953);
    printRandNums(10002);

    return 0;
}
