#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include "../Common/Card.h"
#include "Table.h"
#include "Deck.h"

class Player {
public:
	Player();
	virtual ~Player() {}
	std::vector<Card> hand() const;				// getter for player hand
	std::vector<Card> discardPile() const;		// getter for the player's discarded cards
	virtual Card* takeTurn(Table &table, const std::vector<Card> &legalMoves, Card *card) = 0;
	void printHand() const;						// print hand
	void returnCards();							// empties the player's discard pile and hand
	void giveCard(Card card);					// puts a card in the player's hand
protected:
	Card playCard(Card card);					// protected method that allows a player (of any kind) to play a card
	void discardCard(Card card);				// similarly this method allows a player to discard a card
	void setHand(std::vector<Card> newHand);	// setter for hand.  Needed to allow for copying players
	void setDiscardPile(std::vector<Card> newDiscardPile);	// similarly needed to copy discard pile
private:
	std::vector<Card> _hand;
	std::vector<Card> _discardPile;
	void findAndRemoveCardFromHand(Card card);
};

#endif