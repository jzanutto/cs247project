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

void Player::printHand() const {
	cout << "Your hand: ";
	for(int i = 0; i < _hand.size(); i++) {
		cout << _hand[i];
		if(i < _hand.size() - 1) {
			cout << " ";
		}
	}

	cout << endl;
}

void Player::returnCards() {
	_discardPile.clear();
	_hand.clear();
}

void Player::giveCard(Card card) {
	_hand.push_back(card);
}

Card Player::playCard(Card card) {
	findAndRemoveCardFromHand(card);
	return card;
}

void Player::discardCard(Card card) {
	findAndRemoveCardFromHand(card);
	_discardPile.push_back(card);
}

void Player::setHand(vector<Card> newHand) {
	_hand = newHand;
}

void Player::setDiscardPile(vector<Card> newDiscardPile) {
	_discardPile = newDiscardPile;
}

void Player::findAndRemoveCardFromHand(Card card) {
	vector<Card>::iterator cardLoc = find(_hand.begin(), _hand.end(), card);
	if(cardLoc == _hand.end()) {
		throw "That is not a legal play.";
	} else {
		_hand.erase(cardLoc);
	}
}