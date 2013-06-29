#ifndef _TABLE_
#define _TABLE_

#include <vector>
#include <deque>
#include "Card.h"

class Table {
	public:
		Table();
		~Table();
		std::vector<Card> getPossibleMoves() const;
		std::deque<Card> clubs() const;
		std::deque<Card> diamonds() const;
		std::deque<Card> hearts() const;
		std::deque<Card> spades() const;
		void placeCard(Card card);
	private:
		std::deque<Card> _clubs;
		std::deque<Card> _diamonds;
		std::deque<Card> _hearts;
		std::deque<Card> _spades;
};

#endif