#include "Table.h"
#include <cassert>

using namespace std;

namespace {
	void addSortedToDeque(deque<Card>& cards, Card& c);

	void addSortedToDeque(deque<Card>& cards, Card& c) {
		Card front = cards.front();
		Card back = cards.back();

		if(c.getRank() == front.getRank() - 1) {
			cards.push_front(c);
		} else if(c.getRank() == back.getRank() + 1) {
			cards.push_back(c);
		} else {
			assert(false);
		}
	}
}

Table::Table() {}

Table::~Table() {}

vector<Card> Table::getPossibleMoves() const {
	vector<Card> possibleMoves = vector<Card>();

	if(_spades.empty()) {
		possibleMoves.push_back(Card(SPADE, SEVEN));
	} else {
		if(_clubs.empty()) {
			possibleMoves.push_back(Card(CLUB, SEVEN));
		} else {
			Card front = _clubs.front();

			if(front.getRank() != ACE) {
				possibleMoves.push_back(Card(CLUB, (Rank)(front.getRank() - 1)));
			} 

			Card back = _clubs.back();

			if(back.getRank() != KING) {
				possibleMoves.push_back(Card(CLUB, (Rank)(back.getRank() + 1)));
			}
		}
	}

	return possibleMoves;
}

deque<Card> Table::clubs() const {
	return _clubs;
}

deque<Card> Table::diamonds() const {
	return _diamonds;
}

deque<Card> Table::hearts() const {
	return _hearts;
}

deque<Card> Table::spades() const {
	return _spades;
}

void Table::placeCard(Card card) {
	
	switch(card.getSuit()) {
		case CLUB:
			addSortedToDeque(_clubs, card);
			break;
		case DIAMOND:
			addSortedToDeque(_diamonds, card);
			break;
		case HEART:
			addSortedToDeque(_hearts, card);
			break;
		case SPADE:
			addSortedToDeque(_spades, card);
			break;
		default:
			break;
	}
}