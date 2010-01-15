#include "game.hpp"

const char *Card::_cardnames[] = {
    "Zwei"
    ,"Drei"
    ,"Vier"
    ,"Fünf"
    ,"Sechs"
    ,"Sieben"
    ,"Acht"
    ,"Neun"
    ,"Zehn"
    ,"Bub"
    ,"Dame"
    ,"König"
    ,"Ass"
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
