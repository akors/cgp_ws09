#include "game.hpp"

const char *Card::_cardnames[] = {
    "Sieben"
    ,"Acht"
    ,"Neun"
    ,"Zehn"
    ,"Bub"
    ,"Dame"
    ,"König"
    ,"Ass"
};

const AskingMenu::MenuItem Talon::_menu_items[] =
{
    { "Karte abheben",  12, MENU_DRAW }
    ,{ "Paar ablegen",  10, MENU_DISCARD }
    ,{ "Beenden",       15, MENU_QUIT }
};


void Talon::showCards()
{
    // sort cards to be displayed:
    _cardlist.sort();

    // print cards
    for(
        std::list<Card>::iterator it = _cardlist.begin();
        it != _cardlist.end();
        ++it
    )
    {
        std::cout<<" - "<<*it<<'['<<it->getCardId()<<']';
    }
    std::cout<<" - "<<std::endl;
}

bool Talon::removePair(Card::card_id_t card)
{
    // count occurences of this card, return false if we have less than two
    if(std::count(_cardlist.begin(), _cardlist.end(), Card(card)) < 2)
        return false;

    // find first occurence of the card in the list
    cardlist_t::iterator cur =
        std::find(_cardlist.begin(), _cardlist.end(), Card(card));

    // erase card, find next occurence of the card
    cur = _cardlist.erase(cur);
    cur = std::find(cur, _cardlist.end(), Card(card));

    // erase next card
    _cardlist.erase(cur);

    // we obviosly deleted the two cards, so we can return true
    return true;
}

void Talon::play()
{
    std::cout<<"\n--- Willkommen zum diesjärigen cgp- Kartenspiel! ---\n"
        "Das Ziel dieses Spiels ist es, alle Karten auf der Hand abzulegen.\n"
        "Sie können Karten nur in Paaren ablegen - "
        "haben sie nur einzelne Karten, müssen sie zusätzliche Karten abheben.\n"
        "Viel Spaß!\n\n";

    AskingMenu::MenuItem::item_id_t menu_choice;

    do
    {
        bool pair_existed;
        Card::card_id_t card_id;

        std::cout<<"Ihre Hand: \n"; showCards();
        menu_choice = _game_menu.ask();

        switch(menu_choice)
        {
            case MENU_DRAW:
                // draw new card
                _cardlist.push_back(Card());
                break;
            case MENU_DISCARD:

                std::cout<<"Welche Karte möchten sie ablegen? ";
                card_id = AskingMenu::getChoice();

                // check validity of card id
                if (card_id== Card::card_id_t(-1) || card_id > Card::_num_cards)
                {
                    std::cout<<"Ungültige Auswahl\n";
                    continue;
                }

                // remove card, check that it really existed
                pair_existed = removePair(card_id);
                if(!pair_existed)
                {
                    std::cout<<"Sie haben kein Paar der Karte "<<
                        Card(card_id)<<" auf der Hand!\n";
                }
                else
                {
                    std::cout<<"Karte "<<Card(card_id)<<" abgelegt.\n";
                }

                break;
            case MENU_QUIT:
                // quit game
                std::cout<<"Spiel Beendet\n";
                return;
            default:
                ;// invalid menu choice, do nothing and repeat question
        }

        std::cout<<std::endl;
        if (_cardlist.empty())
            std::cout<<"Sie haben gewonnen! Gratulation!\n";
    } while(!_cardlist.empty());
}
