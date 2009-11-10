#include <iostream>
#include <valarray>

using std::slice;

typedef std::valarray<double> matrix_t;
const unsigned n = 2;

matrix_t read2x2();
void print2x2(const matrix_t& m);

inline
matrix_t::value_type determinant2x2(const matrix_t& m)
{
    return m[0]*m[3] - m[1]*m[2];
}



int main()
{
    try {
        matrix_t mat = read2x2();

        print2x2(mat);
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
    std::cout<<"["; std::cin>>mat[0]; std::cin>>mat[1]; std::cout<<"]\n";
    std::cout<<"["; std::cin>>mat[2]; std::cin>>mat[3]; std::cout<<"]\n";

    return mat;
}

void print2x2(const matrix_t& m)
{
    std::cout<<"["<<m[0]<<", "<<m[1]<<"]\n";
    std::cout<<"["<<m[2]<<", "<<m[3]<<"]\n";
}



