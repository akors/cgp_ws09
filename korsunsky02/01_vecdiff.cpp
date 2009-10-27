#include <iostream>
#include <algorithm>
#include <functional>

#include <cstdlib>
#include <ctime>

const unsigned leng = 4000u;

int main()
{
    // initialize stdlib randon number generator
    srand(time(NULL));

    std::cout<<"Die Zahl der Elemente ist: "<<leng<<'\n';

    // create two vectors with leng size
    int vec1[leng], vec2[leng];

    // fill with random elements
    std::generate_n(vec1, leng, &std::rand);
    std::generate_n(vec2, leng, &std::rand);

    // produce difference vector for comparison of vec1 and vec2
    int compvec[leng]; std::fill_n(compvec, leng, false);
    std::transform(vec1, vec1+leng, vec2, compvec, std::minus<int>());

    // count elements that are greater in vec1
    std::size_t numgreater = std::count_if(
        compvec,
        compvec+leng,
        std::bind2nd(std::greater<int>(),0)
    );

    // count elements that are greater in vec2
    std::size_t numsmaller = std::count_if(
        compvec,
        compvec+leng,
        std::bind2nd(std::less<int>(),0)
    );

    std::cout<<numgreater<<" Elemente von vec1 sind groesser als die "
            "zugehoerigen Elemente in vec2.\n";

    // count elements that are greater in vec2
    std::cout<<numsmaller<<" Elemente von vec1 sind kleiner als die "
            "zugehoerigen Elemente in vec2.\n";

    double prop = static_cast<double>(numgreater) / numsmaller;
    std::cout<<"Das Verhaeltnis der beiden Zahlen ist: "<<prop<<'\n';

    std::cout<<"Strebt die Anzahl der Elemente gegen unendlich, strebt das "
        "Verhaeltnis gegen 1"<<'\n';

    return 0;
}

