#include <iostream>

unsigned factorial(unsigned n)
{
    unsigned result = n;

    while(n > 1)
        result *= --n;

    return result;
}

int main()
{
    for (unsigned i = 1; i <= 10; i++)
        std::cout<<i<<"! = "<<factorial(i)<<std::endl;

    return 0;
}