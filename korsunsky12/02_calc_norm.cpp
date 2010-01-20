#include <iostream>
#include <complex>
#include <valarray>

double norm(const std::valarray<double>& vec)
{
    std::valarray<double> tempvec(vec);
    tempvec *= vec;
    return tempvec.sum();
}

double norm(const std::valarray<std::complex<double> >& vec)
{
    // create temporary vector, complex-conjugate
    std::valarray<std::complex<double> > tempvec(vec);
    tempvec.apply(std::conj);

    // multiply conjugate vector with previous vector
    tempvec *= vec;

    // retrieve sum. The sum should now hold only real values
    std::complex<double> sum = tempvec.sum();

    return sum.real();
}

int main()
{
    const double realnums[] = { 2., 4., 11., 29. };
    std::valarray<double> real_vec(realnums, 4);

    std::complex<double> im_nums[4];
    im_nums[0] = std::complex<double>(1., 0);
    im_nums[1] = std::complex<double>(2., -11);
    im_nums[2] = std::complex<double>(3., 2);
    im_nums[3] = std::complex<double>(4., 1);

    std::valarray<std::complex<double> > imag_vec(im_nums, 4);

    std::cout<<norm(real_vec)<<'\n';
    std::cout<<norm(imag_vec)<<'\n';

    return 0;
}
