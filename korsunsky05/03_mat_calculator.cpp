#include <iostream>
#include <exception>
#include <iterator>
#include <algorithm>

#include "cgp_matrix.hpp"

typedef cgp_matrix::matrix<double> matrix;


void ignore_line ( std::istream& in )
{
    in.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
}

matrix read_matrix()
{
    std::cout<<"Bitte geben Sie die Anzahl der Zeilen und die Anzahl der "
        " Spalten durch ein leerzeichen getrennt an: ";

    matrix::size_type rows, cols;

    std::cin>>rows>>cols;

    matrix out_matrix(rows, cols);

    std::cout<<"Bitte geben sie die Elemente Matrix Zeilenweise, "
        "durch Leerzeichen und/oder Zeilenumbrüche getrennt an: ";


    for (
        matrix::iterator out_it = out_matrix.begin();
        out_it != out_matrix.end();
        ++out_it
    )
    {
        std::cin>>(*out_it);
    }



    return out_matrix;
}

char prompt(const char* text, const char* choices);

// char main_menu()
// {
//     std::cout<<
// }

int main()
{
    // we want cin to throw exceptions in case of trouble
    std::cin.exceptions(std::ios::badbit | std::ios::failbit);

    try {
        std::cout<<"Willkommen zum einfachen Matrizenrechner. ";

        std::cout<<"Geben sie eine Matrix an mit der sie Arbeiten möchten: \n";

        matrix m = read_matrix(), m1;
        std::cout<<m;

        char do_what = prompt(
            "Was möchten sie mit dieser Matrix tun?\n"
            "T: Matrix transponieren\n"
            "A: Matrizen Addieren\n"
            "M: Matrizen multiplizieren\n"
            "c: Mit konstante multiplizieren\n", "TAMc");

        double c;

        switch (do_what)
        {
            case 'T':
                m = m.transpose();
                break;
            case 'c':
                std::cout<<"Bitte geben sie die Konstante an: "; std::cin>>c;
                m = c * m;
                break;
            case 'A':
                std::cout<<"Geben sie die zu addierende Matrix an: \n";
                m1 = matrix(read_matrix());

                if (!(m.columns() == m1.columns() && (m.rows() == m1.rows())))
                {
                    std::cerr<<"Die Matrizen müssen die selbe Dimension haben!\n";
                    return 1;
                }

                m = m + m1;
                break;
            case 'M':
                std::cout<<"Geben sie die zu multiplizierende Matrix an: \n";
                m1 = read_matrix();

                if (m.columns() != m1.rows())
                {
                    std::cerr<<"Die zweite Matrix muss gleich viele Zeilen haben wie die erste Matrix Spalten!\n";
                    return 1;
                }

                m = m * m1;
                break;
            default:
                std::cerr<<"Unbekannte Option "<<do_what<<'\n';
                return 1;
        }

        std::cout<<"Ergebnis:\n"<<m;
    } catch(const std::exception&)
    {
        std::cerr<<"Eingabefehler!\n";
    }

    return 0;
}

char prompt(const char* text, const char* choices)
{
    std::cout<<text<<" [";

    if (*choices != '\0')
        std::cout<<*choices++;

    while (*choices != '\0')
        std::cout<<"/"<<*choices++;

    std::cout<<"] ";

    char answer;
    std::cin>>answer;

    ignore_line(std::cin);

    return answer;
}
