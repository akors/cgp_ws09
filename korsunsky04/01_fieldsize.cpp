#include <iostream>

const char* seperator =
"--------------------------------------------------------------------------------"
;

void beobachtungen();

template <typename T, unsigned i, unsigned j>
void show_sizes()
{
    std::cout<<seperator<<std::endl;
    T field[i][j];

    for (unsigned k = 0; k < i; ++k)
        for(unsigned l = 0; l < j; ++l)
            std::cout<<"\tAddresse des elements f("<<k+1<<","<<l+1<<"): "
                <<&field[k][l]<<"\n";

    std::size_t col_diff =
        reinterpret_cast<size_t>(&field[0][1])
        - reinterpret_cast<size_t>(&field[0][0]);

    std::size_t row_wrap =
        reinterpret_cast<size_t>(&field[1][0])
        - reinterpret_cast<size_t>(&field[0][j-1]);

    std::cout<<'\n';
    std::cout<<"Die Addressen der Elemente einer Zeile unterscheiden sich durch "
        <<col_diff<<" Speichereinheit(en).\n\n";

    std::cout<<"Die Adresse des letzten Elements einer Zeile unterscheidet "
        "sich von der Adresse des ersten Elements der nächsten Zeile durch "
        <<row_wrap<<" Speichereinheit(en).\n\n";
    std::cout<<seperator<<std::endl;
}

int main()
{
    std::cout<<6<<"x"<<3<<" "<<"bool Feld:\n";
    show_sizes<bool, 6, 3>();

    std::cout<<2<<"x"<<12<<" "<<"int Feld:\n";
    show_sizes<int, 2, 12>();

    std::cout<<8<<"x"<<7<<" "<<"double Feld:\n";
    show_sizes<double, 8, 7>();

    beobachtungen();

    return 0;
}


void beobachtungen()
{
    std::cout<<
    "Beobachtungen: \n"
    "Für statisch reservierte Arrays gilt folgendes:\n"
    "Die Elemente eines jeden Feldes liegen in konstantem Abstand voneinander.\n"
    "Bei zweidimensionalen Feldern liegen die Elemente einer Zeile nacheinander;"
    "die Zeilen des Feldes leigen ebenfalls nacheinander im Speicher."
    "\n\n"
    "Der Abstand der Elemente voneinander ist abhängig vom Datentyp der Elemente"
    ".\nFür bool ist dieser "<<sizeof(bool)<<" == sizeof(bool),\n"
    "Für int ist dieser "<<sizeof(int)<<" == sizeof(int),\n"
    "Für double ist dieser "<<sizeof(double)<<" == sizeof(double).\n"
        <<
    "Interpretation:\n"
    "Für statische Arrays und Felder optimiert der verwendete Compiler den "
    "Zugriff auf die Elemente der Felder durch anordnung in reihe.\n";

}
