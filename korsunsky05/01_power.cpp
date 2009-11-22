#include <iostream>
#include <cmath>

int main()
{
    const unsigned nums[] =
        {1, 2, 3, 4, 5, 6, 7, 8};

    unsigned const *base_ptr = nums;
    unsigned const *exp_ptr = nums;
    double (*applyfunc) (double, int) = &std::pow;

    for(unsigned i = 0; i<8; ++base_ptr, ++i)
    {
        for(unsigned j = 0; j<8; ++exp_ptr, ++j)
            std::cout<<*base_ptr<<'^'<<*exp_ptr<<" = "<<applyfunc(*base_ptr, *exp_ptr)<<'\n';

        exp_ptr = nums;
    }

    return 0;
}
