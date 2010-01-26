#include <iostream>
#include <complex>
#include <valarray>

#include <ctime>
#include <cstdlib>


template <typename T>
void show_vec(const std::valarray<T>& v)
{
    if (v.size() != 0)
        std::cout<<v[0];

    for (unsigned i = 1; i < v.size(); ++i)
        std::cout<<", "<<v[i];
}


double norm(const std::valarray<double>& vec)
{
    std::valarray<double> tempvec(vec);
    tempvec *= vec;
    return sqrt(tempvec.sum());
}

double norm(const std::valarray<std::complex<double> >& vec)
{
    // multiply complex conjugate vector with vector
    std::valarray<std::complex<double> > tempvec = vec.apply(std::conj) * vec;

    return sqrt(tempvec.sum().real());
}

inline double rand_dbl()
{
    // produce random numbers in this range
    static const double min = -200., max = 200.;

    return 
        (max - min)*
        (static_cast<double>(rand()) /  static_cast<double>(RAND_MAX))
        + min;
}

inline std::complex<double> rand_cmpl()
{
    return std::complex<double>(rand_dbl(),rand_dbl());
}

int main()
{
    srand(time(NULL));

    // create random double vector
    double realnums[4];
    std::generate_n(realnums, 4, &rand_dbl);
    std::valarray<double> real_vec(realnums, 4);

    std::complex<double> im_nums[4];
    std::generate_n(im_nums, 4, &rand_cmpl);

    std::valarray<std::complex<double> > imag_vec(im_nums, 4);

    std::cout<<"Reeler Vektor: "; show_vec(real_vec); std::cout<<'\n';
    std::cout<<"Norm: "<<norm(real_vec)<<'\n'<<'\n';

    std::cout<<"Imaginaerer Vektor: "; show_vec(imag_vec); std::cout<<'\n';
    std::cout<<"Norm: "<<norm(imag_vec)<<'\n';

    return 0;
}
