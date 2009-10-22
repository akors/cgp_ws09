#include <iostream>
#include <cmath>

const double upper_limit = 1;
const double lower_limit = 0;


void print_sine(double distance);

int main()
{
    std::cout<<"Calculating sine in the interval ["
        <<lower_limit<<", "<<upper_limit<<"].\n";
    std::cout<<"Please enter the distance of the points"
        "as floating point number: ";

    double distance;

    std::cin>>distance;
    if (!std::cin.good())
    {
        std::cerr<<"The number you entered was not a floating point number!\n";
        return 1;
    }

    print_sine(distance);

    return 0;
}


void print_sine(double distance)
{
    unsigned num_points= (upper_limit-lower_limit)/distance, count = 0u;

    while(count <= num_points)
    {
        std::cout<<"sin("<<distance*count<<") = "
            <<sin(distance*count)<<"\n";
        ++count;
    }

    std::cout<<"sin("<<1<<") = "<<sin(1.0)<<"\n";
}
