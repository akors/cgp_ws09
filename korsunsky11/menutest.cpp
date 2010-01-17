#include <iostream>
#include "menu.hpp"

int main()
{
    // menu choices
    AskingMenu::MenuItem items[] =
    {
        {"Christoph Gattringer", 1, 7}
        ,{"Alexander Korsunsky",5, 31}
        ,{"Jemand anderes", 10, 22}
    };

    AskingMenu menu("Wer sind sie?", items, 3);
    AskingMenu::MenuItem::item_id_t choice = menu.ask();
    std::cout<<"The choice was: "<<choice<<'\n';

    menu.ask();

    return 0;
}