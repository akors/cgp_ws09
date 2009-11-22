#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

#include <cstdlib>
#include <ctime>

#include "02_calc_moments.hpp"

const std::size_t numel = 287600;

template <typename InputIterator>
typename std::iterator_traits<InputIterator>::value_type
moment(unsigned n, InputIterator start, InputIterator end);


inline double randgen()
{
    return std::rand()/(RAND_MAX + 1.0);
}

int main()
{
    // initialize stdlib random number generator
    std::srand(std::time(NULL));

    // create two vectors with leng size
    double vec[numel];

    // fill with random elements
    std::generate_n(vec, numel, &randgen);

    // get first moment:
    std::cout<<"Erstes moment: "<<moment(1, vec, vec+numel)<<'\n';
    std::cout<<"Zweites moment: "<<moment(2, vec, vec+numel)<<'\n';
    std::cout<<"Drittes moment: "<<moment(3, vec, vec+numel)<<'\n';
    std::cout<<"Viertes moment: "<<moment(4, vec, vec+numel)<<'\n';
    std::cout<<"Fünftes moment: "<<moment(5, vec, vec+numel)<<'\n';

    // dump the numbers to disk

    // first create a file for writing
    std::ofstream outfile("randnums.txt");
    if(!outfile)
    {
        perror("Konnte Datei nicht oeffnen");
        return 1;
    }

    // I want 12 decimals of precision
    outfile.precision(12);

    // copy the random vector to the file
    std::copy(vec, vec+numel, std::ostream_iterator<double>(outfile,"\n"));

    // the file goes out of scope and closes itself

    return 0;
}
