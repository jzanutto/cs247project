#ifndef _DECK_
#define _DECK_

#include "../Common/Card.h"
#include <vector>

class Deck {
	public:
		Deck(int seed);
		void shuffle();						// provided shuffle method modified to work with our objects
		std::vector<Card> cards() const;	// public getter for the deck
	private:
		std::vector<Card> _deck;
};

std::ostream &operator<<(std::ostream &out, const Deck&);

#endif