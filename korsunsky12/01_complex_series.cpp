#include <iostream>
#include <complex>
#include <fstream>

#include <cstdlib>

const unsigned default_num_iterations = 150;

inline std::complex<double> next_elem(std::complex<double> prev)
{
    return prev * prev;
}

int main(int argc, char* argv[])
{
    unsigned int num_iterations = default_num_iterations;
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

    //

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
        outfile<<current_value.real()<<" "<<current_value.real()<<'\n';
    }

    outfile.close();

    return EXIT_SUCCESS;
}
