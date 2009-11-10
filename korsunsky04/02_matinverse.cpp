#include <iostream>
#include <valarray>
#include <cmath>
#include <limits>

using std::slice;

typedef std::valarray<double> matrix_t;

const unsigned n = 2;



// own comparison function, because comparing for equality doesnt work
// reliably
inline bool is_equal(const double& a, const double& b)
{ return std::fabs(a - b) < std::numeric_limits<double>::epsilon(); }

inline matrix_t::value_type determinant2x2(const matrix_t& m)
{ return m[0]*m[3] - m[1]*m[2]; }

matrix_t m_multiply2x2(const matrix_t& A, const matrix_t& B);
matrix_t invert2x2(const matrix_t& m);
matrix_t read2x2();
void print2x2(const matrix_t& m);

int main()
{
    try {
        matrix_t mat = read2x2();

        std::cout<<"A = \n"; print2x2(mat); std::cout<<"\n\n";

        std::cout<<"det(A) = "<<determinant2x2(mat)<<'\n';

        if(is_equal(determinant2x2(mat),0))
        {
            std::cout<<"Die Determinante ist 0. Kann Inverse Matrix nicht "
                "berechnen\n";
            return 1;
        }

        matrix_t inv = invert2x2(mat);
        std::cout<<"Invertierte Matrix A^-1 = \n";
        print2x2(inv);

        std::cout<<"Probe: A * A^-1 = \n";
        print2x2(m_multiply2x2(mat, inv));
    } catch(...)
    {
        std::cerr<<"Fehler beim Einlesen der Matrix\n";
        return 1;
    }

    return 0;
}

matrix_t read2x2()
{
    using std::istream;
    matrix_t mat(n*n);

    mat = 0;
    // set cin exceptions to throw on error
    std::cin.exceptions(
        istream::eofbit | istream::failbit | istream::badbit);

    std::cout<<"Geben sie die "<<n<<"x"<<n<<" Matrix Zeilenweise ein (trennen"
        "der Elemente durch Leerzeichen):\n";
    std::cout<<"[\n\t";
        std::cin>>mat[0]; std::cin>>mat[1];
    std::cout<<"]\n";
    std::cout<<"[\n\t";
        std::cin>>mat[2]; std::cin>>mat[3];
    std::cout<<"]\n";

    return mat;
}

matrix_t invert2x2(const matrix_t& m)
{
    matrix_t inverted(n*n);

    inverted[0] = m[3];
    inverted[1] = -m[1];
    inverted[2] = -m[2];
    inverted[3] = m[0];

    inverted *= (1.0/determinant2x2(m));

    return inverted;
}

void print2x2(const matrix_t& m)
{
    std::cout<<"["<<m[0]<<", "<<m[1]<<"]\n";
    std::cout<<"["<<m[2]<<", "<<m[3]<<"]\n";
}

matrix_t m_multiply2x2(const matrix_t& A, const matrix_t& B)
{
    matrix_t result(n*n);

    result[0] = A[0]*B[0] + A[1]*B[2];
    result[1] = A[0]*B[1] + A[1]*B[3];
    result[2] = A[2]*B[0] + A[3]*B[2];
    result[3] = A[2]*B[1] + A[3]*B[3];

    return result;
}
