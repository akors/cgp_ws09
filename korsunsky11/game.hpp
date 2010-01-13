#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <list>

#include <cstdlib>
#include <cassert>

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
    { return other._card_id == _card_id; }

    bool operator < (const Card& other) const
    { return other._card_id < _card_id; }

private:
#ifdef USE_SUGGESTED_RANDCODE
    static int nrand(int n)
    {
        const int bucket_size = RAND_MAX / n;
        int r;
        do r = rand() / bucket_size;
        while (r >= n);
        return r;
    }
#else // ifdef USE_SUGGESTED_RANDCODE
    static card_id_t nrand(card_id_t n)
    {
        return rand() % n;
    }
#endif // ifdef USE_SUGGESTED_RANDCODE

    card_id_t _card_id;

    static const std::size_t _num_cards = 13;
    static const char *_cardnames[];
};

inline std::ostream& operator << (std::ostream& os, const Card& card)
{ return os<<card.cardname(); }


#endif // ifndef GAME_HPP_
