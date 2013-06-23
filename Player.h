#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include "Card.h"

class Player {
public:
	Player(std::vector<Card> newHand);
	std::vector<Card> hand() const;				// getter for player hand
	virtual Card playCard() = 0;
	~Player() {}
	void incScore(int points);				// increases the player's score by the number of points passed
	int getScore() const;

private:
	std::vector<Card> _hand;
	int _score;
};

std::ostream &operator<<(std::ostream &out, const Player& p);

#endif