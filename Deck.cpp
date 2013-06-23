#include <iostream>
#include <cstdlib>
#include "Deck.h"


using namespace std;

namespace {
	static const int DECK_SIZE = 52;
}

Deck::Deck() {
	init();
}

Deck::Deck(int seed) {
	init();
	srand48(seed);
	shuffle();
}

/* 
DECK_SIZE is the constant 52
since this is internal, we have _deck as an array of cards
*/

void Deck::shuffle() {
	int n = DECK_SIZE;

	while ( n > 1 ) {
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

void Deck::init() {
	
	for (Suit suit = CLUB; suit < SUIT_COUNT; suit++) {
		for (Rank rank = ACE; rank < RANK_COUNT; rank++) {
	
			_deck.push_back(Card(suit, rank));
		}
	}
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


