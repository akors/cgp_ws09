#include <iostream>
#include <valarray>
#include <cassert>

std::valarray<unsigned> produce_primes(unsigned highest);
void print_primefactors(const std::valarray<unsigned>& primes, unsigned n);


int main()
{
    unsigned n;

    std::cout<<"Geben sie eine Ganzahl ein dessen Primfaktoren bestimmt werden"
        " sollen: ";

    std::cin>>n;
    if(!std::cin.good())
    {
        std::cerr<<"Konnte Wert nicht einlesen. "
            "Sie muessen eine Ganzzahl eingeben!\n";
        return 1;
    }

    // we don't like to compute prime factors for zeros, ones and twos
    if (!(n > 1))
    {
        std::cout<<"Primfaktoren von 0, 1 und 2 sind nicht definiert!\n";
        return 1;
    }

    try {
        std::valarray<unsigned> primes = produce_primes(n);

        std::cout<<"Primfaktoren: ";
        print_primefactors(primes, n);
        std::cout<<"\n";
    } catch(const std::bad_alloc&)
    {
        std::cerr<<"Entschuldigung, die zu untersuchende Zahl ist leider "
            "zu gross. Versuchen sie es bitte mit einer kleineren Zahl!\n";
    }
    return 0;
}

void print_primefactors(const std::valarray<unsigned>& primes, unsigned n)
{
    unsigned i = 0;

    while (n > 1 && i < primes.size())
    {
        // if we found a prime factor,
        if ((n % primes[i]) == 0u)
        {
            // print out the number,
            std::cout<<primes[i]<<" ";

            // divide the number by the prime,
            n /= primes[i];

            // and continue to check if the prime number might be contained
            // several times
            continue;
        }

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
