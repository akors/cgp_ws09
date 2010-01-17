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

    // default constructor, do nothing
    AskingMenu() {}

    // constructor, initialize with an array of menu items
    AskingMenu(
        const std::string& asking_text,
        const MenuItem items[], std::size_t num_items)
        : _asking_text(asking_text)
    {
        for (unsigned i = 0; i < num_items; ++i)
            _menu_items.push_back(items[i]);

        std::sort(_menu_items.begin(), _menu_items.end());
    }

    MenuItem::item_id_t ask();

    static unsigned getChoice();
private:
    typedef std::vector<MenuItem> items_list_t;
    items_list_t _menu_items;
    std::string _asking_text;

    void printMenu() const;
};

#endif // ifndef MENU_HPP_
