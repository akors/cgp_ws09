#include <iostream>
#include "frachtflieger.hpp"

int main()
{
    C_frachtflieger antonov;

    // Beladung des fliegers
    antonov.Belade(2000);

    // frachtueberpruefung
    antonov.Zeiggewicht();

    // Start in die Ferne
    antonov.Speed(300,200, 0);
    antonov.Steig(500);

    // Ueberpruefung der Position
    antonov.Zeigposition(6000);

    // Kurskorrektur
    std::cout<<"Korrigiere Kurs...\n";
    antonov.Speed(360,190, 6000);
    antonov.Steig(100);
    std::cout<<"Kurs korrigiert\n";

    // Positionsabfrage
    antonov.Zeigposition(11000);

    std::cout<<"Setze zum Landeanflug an...\n";
    antonov.Steig(-500);
    antonov.Speed(120,100,11000);

    antonov.Steig(-100);
    antonov.Speed(0,0,12000);
    std::cout<<"Gelandet. Ausladen beginnt...\n";

    antonov.Entlade();

    std::cout<<"Fracht wurde geliefert, Mission erfüllt!\n";

    return 0;
}
