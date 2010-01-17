#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <list>
#include <functional>
#include <iterator>
#include <algorithm>

#include <cstdlib>
#include <cassert>

#include "menu.hpp"

struct Card
{
    typedef unsigned card_id_t;

    // Default constructor, picking random card
    Card()
    {
        _card_id = nrand(_num_cards);
    }

    // Construct a specific card
    explicit Card(card_id_t card_id)
    {
        // We do NOT want any indices higher than our card count
        assert(card_id < _num_cards);

        _card_id = card_id;
    }

    std::string cardname() const
    { return std::string(_cardnames[_card_id]); }

    card_id_t getCardId() const
    { return _card_id; }

    bool operator == (const Card& other) const
    { return _card_id == other._card_id; }

    bool operator < (const Card& other) const
    { return  _card_id < other._card_id; }


    static const std::size_t _num_cards = 13;
private:
    static card_id_t nrand(card_id_t n)
    { return rand() % n; }

    card_id_t _card_id;

    static const char *_cardnames[];
};

inline std::ostream& operator << (std::ostream& os, const Card& card)
{ return os<<card.cardname(); }


class Talon
{
    typedef std::list<Card> cardlist_t;
    std::size_t _start_cards;
    cardlist_t _cardlist;

    AskingMenu _game_menu;
    static const AskingMenu::MenuItem _menu_items[];

   // remove pair from cardlist. if the pair existed, return true
   // otherwise false.
    bool removePair(Card::card_id_t card);

    void showCards();

    enum {
        MENU_DRAW = 0
        ,MENU_DISCARD
        ,MENU_QUIT


        ,MENU_NUM_ITEMS
    };
public:
    // construct Talon game with N cards
    Talon(std::size_t start_cards)
        : _start_cards(start_cards)
    {
        // (ab)using local copy of max_cards variable as counter
        for (start_cards = 0; start_cards < _start_cards; ++start_cards)
            _cardlist.push_back(Card());

        // initialize game menu
        _game_menu = AskingMenu(
            "Heben sie eine Karte ab oder legen sie ein Paar ab!",
            _menu_items, MENU_NUM_ITEMS
        );
    }

    void play();
};

#endif // ifndef GAME_HPP_
