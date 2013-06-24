#include <vector>
#include <iostream>
#include <algorithm>
#include "Player.h"

using namespace std;

Player::Player() {}

vector<Card> Player::hand() const {
	return _hand;
}

vector<Card> Player::discardPile() const {
	return _discardPile;
}

void Player::returnCards() {
	_discardPile.clear();
	_hand.clear();
}

void Player::giveCard(Card card) {
	_hand.push_back(card);
}

void Player::discardCard(Card card) {
	vector<Card>::iterator cardLoc = find(_hand.begin(), _hand.end(), card);

	_hand.erase(cardLoc);
	_discardPile.push_back(card);
}

ostream &operator<<(ostream &out, const Player& p) {
	vector<Card> playerHand = p.hand();
	for (int i = 0; i < playerHand.size(); i++) {
		out << playerHand[i];
		if (i < playerHand.size() - 1) {
			out << " ";
		}
	}
	out << endl;
	return out;
}
