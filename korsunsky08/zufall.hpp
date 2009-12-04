
#ifndef ZUFALL_HPP
#define ZUFALL_HPP

template <
    typename T, // Type of the Data values
    int a, // Parameter a of linear congruency definition
    int b, // Parameter a of linear congruency definition
    unsigned m // Parameter a of linear congruency definition
>
struct generic_C_zufall
{
    generic_C_zufall() {} // default constructor, leave start value undefined
    generic_C_zufall(int L1) : L_n(L1) {} // construct with a start value

    T Getrandom()
    {
        int L_n_1 = L_n;
        L_n = next_number(L_n);

        return static_cast<T>(L_n_1) / m;
    }

    void Seed(int seed) { L_n = seed; } // set seed to other value

private:
    static inline int next_number(int current)
    { return (a + b * current) % m; }

    int L_n;
};

#endif // ZUFALL_HPP
