#include <iostream>
#include <fstream>
#include <cmath>

using std::make_pair;

template <typename BinaryFunction, typename Type1, typename Type2>
bool writePlotData(
    BinaryFunction f,
    const std::pair<Type1, Type1>& x_lims,
    const std::pair<Type2, Type2>& y_lims,
    const std::pair<Type1, Type2>& resolution,
    const char* filename)
{
    std::ofstream outfile;
    outfile.open(filename);

    if (!outfile)
        return false;

    // iterate x values
    for (Type1 x = x_lims.first; x < x_lims.second; x += resolution.first)
        for (Type2 y = y_lims.first; y < y_lims.second; y += resolution.second)
        {
            outfile<<x<<' '<<y<<' '<<f(x,y)<<'\n';
        }

    outfile.close();
    return true;
}

struct Func {
    double operator() (double x, double y)
    { return (x*x + 2.4*y*y - y) * std::exp(1 - (x*x + y*y)); }
};

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr<<"Programm erwarted Dateiname als Argument!\n";
        return 1;
    }

    Func func;

    bool state = writePlotData(
        func,
        make_pair(-2.5,2.5),
        make_pair(-2.5,2.5),
        make_pair(0.3,0.3),
        argv[1]
    );

    if (!state)
    {
        perror("Fehler beim oeffnen der Datei");
    }

    return 0;
}
