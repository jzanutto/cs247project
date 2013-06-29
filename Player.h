#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include "Card.h"

class Player {
public:
	Player();
	virtual ~Player() {}
	std::vector<Card> hand() const;				// getter for player hand
	std::vector<Card> discardPile() const;
	virtual void takeTurn() = 0;
	void printHand() const;
	void returnCards();
	void giveCard(Card card);
protected:
	Card playCard(Card card);
	void discardCard(Card card);
private:
	std::vector<Card> _hand;
	std::vector<Card> _discardPile;
	void findAndRemoveCardFromHand(Card card);
};

#endif