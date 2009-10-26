#include <iostream>
#include <cmath>

unsigned factorial(unsigned n)
{
    unsigned result = n;

    while(n > 1)
        result *= --n;

    return result;
}

void print_pascal(unsigned size, unsigned *pascal[]);

const std::size_t pascal_size = 10;

int main()
{
    // allocate space for the triangle
    unsigned pascal[pascal_size][pascal_size];

    // get two counter variables
    unsigned i, j;

    // fill first column with ones
    for(i = 0; i < pascal_size; ++i)
        pascal[i][0] = 1;

    // iterate through rows, start with the second
    for (i = 1; i < pascal_size; ++i)
    {
        // iterate through colums, start with the second, leave out the last
        for (j = 1; j < i; ++j)
            // assign the field value as sum of the two fields above
            pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];

        // last value is allways one
        pascal[i][i] = 1;
    }

    std::cout<<"Last row: ";
    for (i = 0; i < pascal_size; ++i)
        std::cout<<'|'<<pascal[pascal_size-1][i];


    std::cout<<"Die ersten zehn Zeilen des Pascalschen Dreiecks sind:\n";
    for (i = 0; i < pascal_size; ++i)
    {
        for (j = 0; j <= i; ++j)
            std::cout<<'|'<<pascal[i][j]<<'|';
        std::cout<<std::endl;
    }

    return 0;
}


