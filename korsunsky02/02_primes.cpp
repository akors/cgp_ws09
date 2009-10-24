#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


const unsigned num_primes = 100;
std::vector<unsigned> getPrimesByCount(const unsigned numprimes);

int main()
{
    std::vector<unsigned> primes = getPrimesByCount(num_primes);

    // print out prime numbers
    std::cout<<"Die ersten "<<num_primes<<" Primzahlen sind: "<<'\n';
    std::copy(
        primes.begin(),
        primes.end(),
        std::ostream_iterator<unsigned>(std::cout, "\n")
    );

    return 0;
}


std::vector<unsigned> getPrimesByCount(const unsigned numprimes)
{
    // allocate space for the required numbers of primes
    std::vector<unsigned> primes(numprimes);

    unsigned current_num = 1; // start off from one
    unsigned primecount = 0; // no primes yet

    while(primecount < numprimes)
    {
        // increase current number
        ++current_num;

        // check if the current number is a prime number
        for (unsigned i = 0; i < primecount; ++i)
        {
            // if the current number modulo any of the previous prime numbers
            // is zero, it is not a prime number
            if (!(current_num % primes[i]))
                goto continue_mainloop;
        }

        // if the above loop finished, we have found a prime number
        primes[primecount++] = current_num;

    continue_mainloop:
        ;
    }

    return primes;
}
