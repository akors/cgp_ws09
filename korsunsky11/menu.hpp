#ifndef MENU_HPP_
#define MENU_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct AskingMenu
{
    struct MenuItem
    {
        typedef unsigned item_id_t;

        std::string _choicename; // a text that will be displayed with the coice
        unsigned priority; // the priority of the item. lowest is best.

        // identifier of this menu item. -1 is reserved for invalid!
        item_id_t item_id;

        bool operator < (const MenuItem& other) const
        { return priority < other.priority; }
    };

    // constructor, initialize with an array of menu items
    AskingMenu(
        const std::string& asking_text,
        MenuItem items[], std::size_t num_items)
        : _asking_text(asking_text)
    {
        for (unsigned i = 0; i < num_items; ++i)
            _menu_items.push_back(items[i]);

        std::sort(_menu_items.begin(), _menu_items.end());
    }

    MenuItem::item_id_t ask()
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
private:
    typedef std::vector<MenuItem> items_list_t;
    items_list_t _menu_items;
    std::string _asking_text;

    void printMenu() const
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

    unsigned getChoice() const
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
};

#endif // ifndef MENU_HPP_
