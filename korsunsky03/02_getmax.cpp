#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>

const int leng = 25;


template <typename ForwardIterator>
typename std::iterator_traits<ForwardIterator>::value_type
getmax(ForwardIterator start, ForwardIterator end)
{
    // Pointer to the highest element
    ForwardIterator highest = start;

    // Iterate through all elements
    // if the current number is greater than the highest number, assign
    // it to the new highest number
    while (start < end)
        if(*(++start) > *highest)
            highest = start;

    return *highest;
}

int main()
{
    // initialize stdlib random number generator
    std::srand(std::time(NULL));

    // produce random number vector with leng elements
    int vec[leng];
    std::generate_n(vec, leng, &std::rand);


    // get highest element of the vector, print output
    std::cout<<"Das hoechste Element des Vektors ist: "<<getmax(vec, vec+leng)
        <<std::endl;

    return 0;
}



