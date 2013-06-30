#ifndef _TABLE_
#define _TABLE_

#include <vector>
#include <deque>
#include <iostream>
#include "Card.h"

class Table {
	public:
		Table();
		~Table();
		std::vector<Card> getPossibleMoves() const;		// generates possible moves for all straight card lists
		std::deque<Card> clubs() const;					// returns the list of clubs on the table
		std::deque<Card> diamonds() const;				// returns the list of diamonds on the table 
		std::deque<Card> hearts() const;				// returns the list of spades on the table
		std::deque<Card> spades() const;				// returns the list of spades on the table
		void placeCard(Card card);						// adds a card to the cards on the table if it is valid
	private:
		std::deque<Card> _clubs;
		std::deque<Card> _diamonds;
		std::deque<Card> _hearts;
		std::deque<Card> _spades;
};

std::ostream& operator<<(std::ostream &out, const Table &table);

#endif