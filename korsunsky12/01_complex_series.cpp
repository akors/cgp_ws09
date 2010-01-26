#include <iostream>
#include <sstream>
#include <complex>
#include <limits>
#include <fstream>

#include <cstdlib>


const double _inf = std::numeric_limits<double>::infinity();

inline bool is_finite(const std::complex<double>& c)
{
    return 
        (c.real() == c.real()) && (c.imag() == c.imag()) &&
        (fabs(c.real()) != _inf) && (fabs(c.imag() != _inf))
            ;
    // a double compared to itself returns false only if it is nan
}

inline std::complex<double> next_elem(std::complex<double> prev)
{
    return prev * prev;
}

int main(int argc, char* argv[])
{
    unsigned int num_iterations;
    std::string outfilename;

    // if we got a parameter passed in, we use it as the output filename,
    // otherwise ask
    if (argc > 1)
    {
        outfilename = argv[1];
    }
    else
    {
        std::cout<<"Bitte geben sie den Namen der Datei an in die"
            "geschrieben werden soll: ";

        std::cin>>outfilename;
    }

    std::cout<<"Bitte geben sie Anzahl der Iterationen an: ";
    std::cin>>num_iterations;

    if (!std::cin.good())
    {
        std::cerr<<"Eingabefehler";
        return EXIT_FAILURE;
    }


    // complex number with radius and argument
    double r, phi;

    std::cout<<"Bitte geben sie ein komplexe Zahl in polardarstellung ein\n"
        "(Betrag und Argument durch Leerzeichen getrennt): ";
    std::cin>>r>>phi;

    if (!std::cin.good())
    {
        std::cerr<<"Fehler bei der Eingabe!\n";
        return EXIT_FAILURE;
    }

    // try to open file
    std::ofstream outfile(outfilename.c_str());
    std::complex<double> current_value = std::polar(r, phi);

    // write the series into the filename
    for (unsigned i = 0; i < num_iterations; ++i)
    {
        current_value = next_elem(current_value);

        // write only if the number is finite
        if(is_finite(current_value))
            outfile<<current_value.real()<<"  "<<current_value.imag()<<'\n';
    }

    outfile.close();

    return EXIT_SUCCESS;
}
