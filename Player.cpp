#include <vector>
#include <iostream>
#include "Player.h"

using namespace std;

Player::Player(vector<Card> newHand) {
	_hand = newHand;
	_score = 0;

}

vector<Card> Player::hand() const {
	return _hand;
}

void Player::incScore(int points) {
	_score = points;
}

int Player::getScore() const {
	return _score;
}

ostream &operator<<(ostream &out, const Player& p) {
	for (vector<Card>::iterator it = p.hand().begin(); it != p.hand().end(); it++) {
		out << *it;
		if (it < p.hand().end()) {
			out << " ";
		}
	}
	out << endl;
	return out;
}
