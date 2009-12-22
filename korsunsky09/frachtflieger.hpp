#include <iostream>

#include "flieger.hpp"

class C_frachtflieger : public C_flieger
{
    unsigned ladegewicht;
public:
    C_frachtflieger() : ladegewicht(0u) {}
    C_frachtflieger(unsigned _ladegewicht) : ladegewicht(_ladegewicht) {}

    void Belade(unsigned _ladegewicht) { ladegewicht = _ladegewicht; }
    void Entlade() { ladegewicht = 0u; }
    void Zeiggewicht() { std::cout<<"Ladegewicht: "<<ladegewicht<<'\n'; }
};
