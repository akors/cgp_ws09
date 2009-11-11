#include <iostream>
#include <valarray>
#include <cassert>

std::valarray<unsigned> produce_primes(unsigned highest);
void print_primefactors(const std::valarray<unsigned>& primes, unsigned n);


int main()
{
    unsigned n;

    std::cout<<"Geben sie eine Ganzahl ein dessen Primfaktoren bestimmt werden"
        " sollen:";

    std::cin>>n;
    if(!std::cin.good())
    {
        std::cerr<<"Sie muessen eine Ganzzahl eingeben!\n";
        return 1;
    }

    std::valarray<unsigned> primes = produce_primes(n);

    std::cout<<"Primfaktoren: ";
    print_primefactors(primes, n);
    std::cout<<"\n";

    return 0;
}

void print_primefactors(const std::valarray<unsigned>& primes, unsigned n)
{
    unsigned i = 0;

    while (primes[i] < n/2 && i < primes.size())
    {
        if ((n % primes[i]) == 0u)
            std::cout<<primes[i]<<" ";

        ++i;
    }
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
