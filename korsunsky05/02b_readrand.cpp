#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

#include "02_calc_moments.hpp"

int main()
{
    // open file for reading
    std::ifstream infile("randnums.txt");
    if(!infile)
    {
        perror("Konnte Datei nicht oeffnen");
        return 1;
    }

    // create a vector for the numbers
    std::vector<double> randvec;

    // create two iterators to read the values
    std::istream_iterator<double> eos; // one to compare with the end of stream
    std::istream_iterator<double> in_it(infile); // one for reading

    //
    std::cout<<"Einlesen der Zahlen ...\n";

    // read file successively
    while (in_it != eos)
        randvec.push_back(*in_it++);

    std::cout<<"randvec hat "<<randvec.size()<<" Elemente.\n\n";

    // get moments:
    std::cout<<"Erstes moment: "<<moment(1, randvec.begin(), randvec.end())<<'\n';
    std::cout<<"Zweites moment: "<<moment(2, randvec.begin(), randvec.end())<<'\n';
    std::cout<<"Drittes moment: "<<moment(3, randvec.begin(), randvec.end())<<'\n';
    std::cout<<"Viertes moment: "<<moment(4, randvec.begin(), randvec.end())<<'\n';
    std::cout<<"Fünftes moment: "<<moment(5, randvec.begin(), randvec.end())<<'\n';

    return 0;
}
