#include "menu.hpp"

AskingMenu::MenuItem::item_id_t AskingMenu::ask()
{
    // print menu
    printMenu();

    // get choice
    std::cout<<"Auswahl: ";
    unsigned choice = getChoice();

    // check choice for correctness
    if (choice < 1 || choice > _menu_items.size())
    {
        std::cout<<"Ungültige Auswahl!\n";
        return -1;
    }

    std::cout<<std::endl;

    // getChoice() returns a menu item starting with one
    return _menu_items[choice-1].item_id;
}

void AskingMenu::printMenu() const
{
    // print the text asking for options
    std::cout<<_asking_text<<'\n';

    unsigned count = 1;
    // print available choices:
    for (items_list_t::const_iterator it = _menu_items.begin();
        it != _menu_items.end(); ++it, ++count)
        std::cout<<" ["<<count<<"] "<<it->_choicename<<'\n';

    std::cout<<std::flush;
}

unsigned AskingMenu::getChoice() const
{
    MenuItem::item_id_t choice;
    std::cin>>choice;

    // if there was an error, return -1
    if(!std::cin.good())
    {
        choice = -1;
    }

    // clean the input stream
    std::cin.clear();
    while(std::cin.get() != '\n');

    return choice;
}
