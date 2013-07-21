#include "GameMaster.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

GameMaster::GameMaster() : _deck(0) {
	for(int i = 0; i < PLAYER_COUNT; i++) {
		_scores[i] = INITIAL_SCORE;
	}	
}

GameMaster::~GameMaster() {
	for (int i = 0; i < PLAYER_COUNT; i++) {
		Player *p = _players[i];
		if(p != NULL) {
			delete p;
		}
	}
}

void GameMaster::seedDeck(int seed) {
	_deck = Deck();
}

void GameMaster::registerPlayers(const bool &players[4]) {
	for (int i = 0; i < PLAYER_COUNT; i++) {
		if (players[i] == true) {
			_players[i] = new HumanPlayer();

		} else {
			_players[i] = new ComputerPlayer();
		}
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
			p->giveCard(c);

			//Assign the first player
			if(c == sevenOfSpades) {
				_currentPlayerNumber = i;
			}

			j++;
		} while(j % (deckCards.size()/PLAYER_COUNT) != 0);	//Breaks after we've dealt a quarter of a deck to a player
	}
}

void GameMaster::takeCurrentPlayerTurn() {
	Player *currentPlayer = _players[_currentPlayerNumber];
	vector<Card> validMoves = legalMoves();
	Card playedCard = Card(SPADE,ACE);

	try {
		playedCard = currentPlayer->takeTurn(_table, _deck, validMoves);
	} catch (const exception &e) {
		if ((string)(e.what()) == "This player ragequit") {
			//Replace the current player with a computer, ragequit
			Player *computerReplacement = new ComputerPlayer(*dynamic_cast<HumanPlayer*>(currentPlayer));
			cout << "Player " << (_currentPlayerNumber + 1) << " ragequits. A computer will now take over." << endl;
			_players[_currentPlayerNumber] = computerReplacement;
			delete currentPlayer;

			//Take the turn properly
			currentPlayer = computerReplacement;
			playedCard = currentPlayer->takeTurn(_table, _deck, validMoves);
		} else {
			exit(0);
		}
	}
	 

	cout << "Player " << (_currentPlayerNumber + 1) << " ";

	if(validMoves.empty()) {
		cout << "discards ";
	} else {
		cout << "plays ";
	} 	

	cout << playedCard << "." << endl;

	//Loop around if we get to player 4
	if(_currentPlayerNumber == PLAYER_COUNT - 1) {
		_currentPlayerNumber = 0;
	} else {
		_currentPlayerNumber++;
	}
}

void GameMaster::beginRound() {
	cout << "A new round begins. It's player " 
		 << (_currentPlayerNumber + 1)
		 << "'s turn to play."
		 << endl;
	
	for(int i = 0; i < _deck.cards().size(); i++) {
		//takeCurrentPlayerTurn();
	}

	for(int i = 0; i < PLAYER_COUNT; i++) {
		Player *player = _players[i];
		vector<Card> discardPile = player->discardPile();

		int playerScore = 0;

		cout << "Player " << i + 1 << "'s discards: ";

		for(int j = 0; j < discardPile.size(); j++) {
			Card card = discardPile[j];

			cout << card;

			if(j < discardPile.size() - 1) {
				cout << " ";
			}

			playerScore += (card.getRank() + 1);
		}

		cout << endl;

		cout << "Player " << i + 1 << "'s score: " 
			 << _scores[i] << " + " << playerScore
			 << " = ";

		_scores[i] += playerScore;

		cout << _scores[i] << endl;

		player->returnCards();
	}

	_table = Table();
}

bool GameMaster::isGameOver() const {
	for(int i = 0; i < PLAYER_COUNT; i++) {
		if(_scores[i] >= END_GAME_SCORE) {
			return true;
		}
	}

	return false;
}

vector<int> GameMaster::winners() const {
	int min = _scores[0];

	for(int i = 1; i < PLAYER_COUNT; i++) {
		if(_scores[i] < min) {
			min = _scores[i];
		}
	}

	vector<int> winningPlayerNumbers = vector<int>();

	for(int i = 0; i < PLAYER_COUNT; i++) {
		if(_scores[i] == min) {
			winningPlayerNumbers.push_back(i + 1);
		}
	}

	return winningPlayerNumbers;
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