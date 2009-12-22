#include <string>
#include <algorithm>
#include <cctype>

#include <iostream>
#include <iomanip>
#include <fstream>

using std::ios;

void display_histogram(unsigned charcount[ 'z' - 'a' + 1]);

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr<<"Programm erwartet Dateiname als Argument!\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile)
    {
        perror("Konnte Datei nicht öffnen");
        return 1;
    }

    // get length of file
    infile.seekg (0, ios::end);
    unsigned filesize = infile.tellg();
    infile.seekg (0, ios::beg);

    // allocate string with appropriate size
    char *filestr = new char[filesize+1];

    // read file into the string
    infile.read(filestr, filesize);
    filestr[filesize] = '\0';

    // close file, we don't need it anymore
    infile.close();

    // array for the character count
    unsigned charcount[ 'z' - 'a' + 1];

    for (unsigned letter = 'a'; letter <= 'z'; ++letter)
    {
        // count number of lowercase letters
        charcount[letter - 'a'] = std::count(filestr, filestr+filesize, letter);

        // count number of uppercase letters
        charcount[letter - 'a']
            += std::count(filestr, filestr+filesize, toupper(letter));
    }

    std::cout<<"\nAnzahl der Buchstaben:\n";
    display_histogram(charcount);

    delete[] filestr;
    return 0;
}

void display_histogram(unsigned charcount[ 'z' - 'a' + 1])
{
    const unsigned histogram_width = 60u;

    float fraction;
    unsigned disp_width;

    // retrieve highest letter count
    unsigned max_count = *std::max_element(charcount, &charcount['z'-'a'+1]);

    for (unsigned letter = 'a'; letter <= 'z'; ++letter)
    {
        fraction = static_cast<float>(charcount[letter - 'a']) / max_count;
        disp_width = fraction * histogram_width;

        std::cout<<"Buchstabe "<<static_cast<char>(letter)<<": "<<
            std::setw(4)<<charcount[letter - 'a']<<" | ";

        for (unsigned i = 0u; i < disp_width; ++i)
            std::cout<<'*';

        std::cout<<'\n';
    }
}
