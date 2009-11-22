#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iterator>

#include <cmath>
#include <cstdlib>
#include <ctime>

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

    return 0;
}

template <typename InputIterator>
typename std::iterator_traits<InputIterator>::value_type
moment(unsigned n, InputIterator start, InputIterator end)
{
    // allocate intermediate array with the same size as the vector
    std::vector<typename std::iterator_traits<InputIterator>::value_type>
    powered(end - start);

    // apply pow function to every element
    std::transform(
        start,
        end,
        powered.begin(),
        std::bind2nd(
          std::ptr_fun<typename std::iterator_traits<InputIterator>::value_type,
            unsigned, typename std::iterator_traits<InputIterator>::value_type>(std::pow), n)
    );


    // sum up all elements of the powered vector
    typename std::iterator_traits<InputIterator>::value_type
    sum = std::accumulate(powered.begin(), powered.end(), 0.0);

    // return moment number
    return sum / (end - start);
}
