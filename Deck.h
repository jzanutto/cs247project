#ifndef _DECK_
#define _DECK_

#include "Card.h"
#include <vector>

class Deck {
public:
	Deck();
	Deck(int seed);
	void shuffle();
	std::vector<Card> cards() const;	// public getter for the deck
	Card pop();							// flips the top card on the deck, deals it out and puts it on the bottom

private:
	void init();						// for constructor delegation purposes
	void initialShuffle(int seed);
	std::vector<Card> _deck;

};

std::ostream &operator<<(std::ostream &out, const Deck&);

#endif