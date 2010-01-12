#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

int main()
{
    // create a vector for the numbers
    std::vector<double> daten;

    std::cout<<"Bitte geben sie die Messdaten ein.\n"
        "Zum beenden drücken sie Ctrl-D: \n\n";

    // create two iterators to read the values
    std::istream_iterator<double> eos; // one to compare with the end of stream
    std::istream_iterator<double> in_it(std::cin); // one for reading

    // read input values
    while (in_it != eos)
        daten.push_back(*in_it++);

    if (daten.size() <= 2)
    {
        std::cerr<<daten.size()<<
            " Werte sind zuwenig. Mindestens 3 werden benötigt!\n";
        return 1;
    }

    // sort, delete highest and lowest values
    std::sort(daten.begin(), daten.end());
    daten.pop_back();
    daten.erase(daten.begin());

    double median = daten[ daten.size() / 2 + (daten.size() % 2) ];
    double mean = std::accumulate(daten.begin(), daten.end(), 0.0) / daten.size();

    std::cout<<"\nMedian: "<<median<<"\nMittelwert: "<<mean<<'\n';
    return 0;
}
