#include <iostream>
#include <valarray>
#include <cassert>

std::valarray<unsigned> produce_primes(unsigned highest);


int main()
{
    std::valarray<unsigned> primes = produce_primes(10000000);

    std::cout<<"Primes up to "<<primes.size()<<":\n";
    for (unsigned i = 0; i < primes.size(); ++i)
        std::cout<<primes[i]<<" ";
    std::cout<<'\n';

    return 0;
}

// Produce primes with the Sieve of Eratosthenes
std::valarray<unsigned> produce_primes(unsigned highest)
{
    // we don't compute primes smaller than two
    assert(highest > 1u);

    // produce a vector with values ranging from one to highest
    std::valarray<unsigned> numbers_vector(highest-2);
    for (unsigned i = 0; i < highest-2; ++i)
        numbers_vector[i] = i+2;

    // produce an bool vector marking all primes
    std::valarray<bool> primes_indices(true, highest-2);

    // iterate through the numbers, kick out all non-primes consecutively
    for (unsigned i = 0; i < highest-2u; ++i)
    {
        // if the current number was kicked out before, continue
        if (!primes_indices[i])
            continue;

        // if the number is still in the array, it must be a prime
        // (otherwise it would have been kicked out before)
        // having a prime number, we can kick out all multiples of this number
        for (unsigned j = i + (i+2); j < highest-2; j += (i+2))
            primes_indices[j] = false;

    }

    return numbers_vector[primes_indices];
}
