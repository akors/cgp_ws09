#include <iostream>
#include <cmath>

double f(double sigma, double x, double y);

int main()
{
    double sigma, x, y;

    std::cout<<"--- Berechnung einer reellen Funktion f ---\n"
               "Geben sie die Argumente und Parameter der Funktion an:\n";

    std::cout<<"\tsigma: ";
    std::cin>>sigma;
    if (!std::cin.good())
    {
        std::cerr<<"Sie muessen eine Fliesskommazahl angeben!\n";
        return 1;
    }
    if (!(sigma > 0.0))
    {
        std::cout<<"Sigma muss groesser als 0 sein.\n";
        return 1;
    }

    std::cout<<"\tx: ";
    std::cin>>x;
    if (!std::cin.good())
    {
        std::cerr<<"Sie muessen eine Fliesskommazahl angeben!\n";
        return 1;
    }

    std::cout<<"\ty: ";
    std::cin>>y;
    if (!std::cin.good())
    {
        std::cerr<<"Sie muessen eine Fliesskommazahl angeben!\n";
        return 1;
    }

    std::cout<<"\nf_"<<sigma<<"("<<x<<", "<<y<<") = "<<f(sigma, x, y)<<'\n';
}

double f(double sigma, double x, double y)
{
    return std::exp(-(x*x + y*y)/(2*sigma));
}
