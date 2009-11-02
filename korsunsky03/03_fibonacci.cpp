#include <iostream>

const unsigned fib_limit = 40;

unsigned slow_fibonacci(unsigned n);

int main()
{
    unsigned n;

    std::cout<<"Geben sie eine Natuerliche Zahl an: ";
    std::cin>>n;
    if (!std::cin.good())
    {
        std::cerr<<"Sie muessen eine Natuerliche Zahl angeben!\n";
        return 1;
    }

    if (n > fib_limit)
    {
        std::cout<<"\nDer verwendete Algorithmus koennte fuer hohe n sehr lange "
            "brauchen. Sind sie sicher, dass sie ein n > "<<fib_limit<<
            " verwenden wollen? [y/n]";

        char answer = '\0';
        std::cin>>answer;
        std::cout<<std::endl;

        if (answer != 'y')
            return 1;
    }

    std::cout<<"Die "<<n<<"-te Fibonacci Zahl ist "<<slow_fibonacci(n)<<".\n";
    return 0;
}

unsigned slow_fibonacci(unsigned n)
{
    switch (n)
    {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return slow_fibonacci(n-1) + slow_fibonacci(n-2);
    }
}
