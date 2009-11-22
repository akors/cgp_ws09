#ifndef CALC_MOMENTS_HPP_
#define CALC_MOMENTS_HPP_

#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iterator>

#include <cmath>

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

#endif // CALC_MOMENTS_HPP_
