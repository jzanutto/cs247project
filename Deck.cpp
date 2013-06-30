#include <iostream>
#include <cstdlib>
#include "Deck.h"


using namespace std;

namespace {
	static const int DECK_SIZE = 52;
}

Deck::Deck(int seed) {
	// generating the deck
	for (int suit = CLUB; suit < SUIT_COUNT; suit++) {
		for (int rank = ACE; rank < RANK_COUNT; rank++) {
			_deck.push_back(Card((Suit)suit, (Rank)rank));
		}
	}
	srand48(seed);
}

/* 
DECK_SIZE is the constant 52
since this is internal, we have _deck as an array of cards
*/

void Deck::shuffle() {
	int n = DECK_SIZE;

	while (n > 1) {
		int k = (int) (lrand48() % n);
		--n;
		Card c = _deck[n];
		_deck[n] = _deck[k];
		_deck[k] = c;
	}
}

vector<Card> Deck::cards() const {
	return _deck;
}

ostream &operator<<(ostream &out, const Deck& deck) {
	vector<Card> myCards = deck.cards();

	for (int i = 1; i <= DECK_SIZE; i++) {
		
		out << myCards[i-1];
		
		if (i % RANK_COUNT != 0) {
			out << " ";
		}
		else {
			out << endl;
		}
	}

	return out;
}


