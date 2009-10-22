#include <iostream>
#include <cmath>

const unsigned low_lim = 1;
const unsigned up_lim = 8;

int main()
{
    for(unsigned k = low_lim; k <= up_lim; k++)
        for(unsigned n = low_lim; n <= up_lim; n++)
            std::cout<<k<<'^'<<n<<" = "<<pow(k, n)<<'\n';

    return 0;
}
