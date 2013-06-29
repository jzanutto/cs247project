#include "GameMaster.h"
#include "HumanPlayer.h"
#include <iostream>
#include <algorithm>
#include <iostream>

using namespace std;

GameMaster::GameMaster() {}

GameMaster::GameMaster(int seed) : _deck(seed) {}

GameMaster::~GameMaster() {
	for (int i = 0; i < PLAYER_COUNT; i++) {
		Player *p = _players[i];
		if(p != NULL) {
			delete p;
		}
	}
}

void GameMaster::registerPlayer(char playerType, int playerNum) {
	if (playerNum <= PLAYER_COUNT) {
		Player *newPlayer = new HumanPlayer();
		_players[playerNum] = newPlayer;
	}
}

Deck GameMaster::deck() const {
	return _deck;
}

Table GameMaster::table() const {
	return _table;
}

void GameMaster::deal() {
	Card sevenOfSpades = Card(SPADE, SEVEN);
	_deck.shuffle();
	vector<Card> deckCards = _deck.cards();

	int j = 0;
	for(int i = 0; i < PLAYER_COUNT; i++) {
		Player *p = _players[i];
		
		do {
			Card c = deckCards[j];
			//cout << c << endl;
			p->giveCard(c);

			if(c == sevenOfSpades) {
				_startingPlayerNumber = i;
			}

			j++;
		} while(j % (deckCards.size()/PLAYER_COUNT) != 0);
	}
	_currentPlayerNumber = _startingPlayerNumber;
}

int GameMaster::currentPlayerNumber() const {
	return _currentPlayerNumber;
}

Player* GameMaster::getPlayer(int playerNumber) const {
	return _players[playerNumber];
}

void GameMaster::printLegalMoves() const {
	vector<Card> cards = legalMoves();
	cout << "Legal plays: ";

	for(int i= 0; i < cards.size(); i++) {
		cout << cards[i];
		if(i != cards.size() - 1) {
			cout << " ";
		}
	}

	cout << endl;
}

vector<Card> GameMaster::legalMoves() const {
	vector<Card> allPossibleMoves = _table.getPossibleMoves();
	vector<Card> playerHand = _players[_currentPlayerNumber]->hand();
	vector<Card> validMoves = vector<Card>();

	for(int i = 0; i < playerHand.size(); i++) {
		Card card = playerHand[i];
		if(find(allPossibleMoves.begin(), allPossibleMoves.end(), card) != allPossibleMoves.end()) {
			validMoves.push_back(card);
		}
	}

	return validMoves;
}