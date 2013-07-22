#include "Table.h"
#include <cassert>

using namespace std;

namespace {
	// helper function that finds where to place a specific card in any generic pile
	void addSortedToDeque(deque<Card>& cards, Card& c) {
		if(cards.empty()) {
			cards.push_front(c);
			return;
		}
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
	// generates potential moves and adds them to the passed list of moves
	void addMovesForSuit(vector<Card> &moves, const deque<Card> &playedCards, const Suit &suit) {
		if (playedCards.empty()) {
			moves.push_back(Card(suit, SEVEN));
		} else {
			Card front = playedCards.front();
			
			if(front.getRank() != ACE) {
				moves.push_back(Card(suit, (Rank)(front.getRank() - 1)));
			} 

			Card back = playedCards.back();

			if(back.getRank() != KING) {
				moves.push_back(Card(suit, (Rank)(back.getRank() + 1)));
			}
		}
	}

	// special print method for special ranks
	void printCardsWithoutSuit(ostream &out, const deque<Card> &cards) {
		for(int i = 0; i < cards.size(); i++) {
			Rank rank = cards[i].getRank();
			// special cases for lettered ranks
			switch(rank) {
				case ACE:
					out << "A";
					break;
				case JACK:
					out << "J";
					break;
				case QUEEN:
					out << "Q";
					break;
				case KING:
					out << "K";
					break;
				default:
					out << (rank + 1);
			}

			if(i != cards.size() - 1) {
				out << " ";
			}
		}

		out << endl;
	}
}

Table::Table() {}

Table::~Table() {}

vector<Card> Table::getPossibleMoves() const {
	vector<Card> possibleMoves = vector<Card>();

	if(_spades.empty()) {
		possibleMoves.push_back(Card(SPADE, SEVEN));
	} else {
		addMovesForSuit(possibleMoves, _clubs, CLUB);
		addMovesForSuit(possibleMoves, _diamonds, DIAMOND);
		addMovesForSuit(possibleMoves, _hearts, HEART);
		addMovesForSuit(possibleMoves, _spades, SPADE);
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

ostream& operator<<(ostream &out, const Table &table) {
	out << "Cards on the table: " << endl;

	out << "Clubs: ";
	printCardsWithoutSuit(out, table.clubs());

	out << "Diamonds: ";	
	printCardsWithoutSuit(out, table.diamonds());

	out << "Hearts: ";	
	printCardsWithoutSuit(out, table.hearts());

	out << "Spades: ";	
	printCardsWithoutSuit(out, table.spades());

	return out;
}