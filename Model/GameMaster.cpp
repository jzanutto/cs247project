#include "GameMaster.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

GameMaster::GameMaster() : _deck(0), _isNewRound(false), _isRoundOver(false), _currentPlayerNumber(-1), _lastCardPlayed(NULL) {
	//Initialize everything to default values
	for(int i = 0; i < PLAYER_COUNT; i++) {
		_scores[i] = INITIAL_SCORE;
		_players[i] = NULL;
	}
}

GameMaster::~GameMaster() {
	//Delete players
	for (int i = 0; i < PLAYER_COUNT; i++) {
		Player *p = _players[i];
		if(p != NULL) {
			delete p;
		}
	}

	//Delete the last card played
	if(_lastCardPlayed != NULL) {
		delete _lastCardPlayed;
	}
}

void GameMaster::seedDeck(int seed) {
	_deck = Deck(seed);
}

void GameMaster::registerPlayers(const bool *players) {
	for (int i = 0; i < PLAYER_COUNT; i++) {		
		if (players[i] == HUMAN) {
			_players[i] = new HumanPlayer();
		} else {
			_players[i] = new ComputerPlayer();
		}
		_playerTypes[i] = players[i];
	}
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

void GameMaster::takeCurrentPlayerTurn(int cardIndex) {
	if(_currentPlayerNumber == -1) {
		return;
	}

	Player *currentPlayer = _players[_currentPlayerNumber];	
	vector<Card> validMoves = legalMoves();

	//Check if the card is in the hand, otherwise we ignored it
	if(cardIndex < currentPlayer->hand().size()) {
		Card playedCard = currentPlayer->hand()[cardIndex];

		_lastCardPlayed = currentPlayer->takeTurn(_table, validMoves, &playedCard);

		incrementPlayer();

		notify();
		//Check if the index indicates a computer player		
	} else if(cardIndex == COMPUTER_PLAYER_CARD_INDEX) {
		if(_lastCardPlayed == NULL) {	//Delete the previously played card
			delete _lastCardPlayed;
		}

		Card *played = new Card(SPADE, ACE);
		_lastCardPlayed = currentPlayer->takeTurn(_table, validMoves, played);

		incrementPlayer();		
		
		notify();
	} else {
		_lastCardPlayed = NULL;
	}

	//update the current player
	currentPlayer = _players[_currentPlayerNumber];

	//Check if the round is over. If the new current player is out of cards
	if(currentPlayer->hand().empty()) {
		_isRoundOver = true;
		stringstream output;

		//Create the round results
		for(int i = 0; i < PLAYER_COUNT; i++) {
			Player *player = _players[i];
			vector<Card> discardPile = player->discardPile();

			int playerScore = 0;

			output << "Player " << i + 1 << "'s discards: ";

			for(int j = 0; j < discardPile.size(); j++) {
				Card card = discardPile[j];

				output << card;

				if(j < discardPile.size() - 1) {
					output << " ";
				}

				playerScore += (card.getRank() + 1);
			}

			output << endl;

			output << "Player " << i + 1 << "'s score: " 
				 << _scores[i] << " + " << playerScore
				 << " = ";

			_scores[i] += playerScore;
			cout << playerScore << endl;

			output << _scores[i] << endl;

			player->returnCards();
		}

		_roundResult = output.str();
		_lastCardPlayed = NULL;
		
		_table = Table();
		notify();

		//Check if the game is over as well
		if (!isGameOver()) {
			//Begin the new round
			deal();
			beginRound();
		} else {
			//Reset everything, game over
			reset();
		}
	}

	//If the next player is a computer player, take their turn
	if(_playerTypes[_currentPlayerNumber] == !HUMAN) {
		takeCurrentPlayerTurn(COMPUTER_PLAYER_CARD_INDEX);
	}	
}

void GameMaster::beginRound() {
	cout << "A new round begins. It's player " 
		 << (_currentPlayerNumber + 1)
		 << "'s turn to play."
		 << endl;
	_isNewRound = true;
	_isRoundOver = false;
	notify();

	if(_playerTypes[_currentPlayerNumber] == !HUMAN) {
		takeCurrentPlayerTurn(COMPUTER_PLAYER_CARD_INDEX);
	}	
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

vector<Card> GameMaster::hand() const {
	Player *currentPlayer = _players[_currentPlayerNumber];
	return currentPlayer->hand();
}

bool GameMaster::isNewRound() {
	bool result = _isNewRound;
	_isNewRound = false;
	return result;
}

bool GameMaster::isRoundOver() {
	bool result = _isRoundOver;
	_isRoundOver = false;
	return result;
}

int GameMaster::currentPlayer() const {
	return _currentPlayerNumber;
}

Card* GameMaster::lastCardPlayed() const {
	return _lastCardPlayed;
}

vector<int> GameMaster::numberOfDiscards() const {
	vector<int> discards = vector<int>(PLAYER_COUNT);
	for(int i = 0; i < PLAYER_COUNT; i++) {
		discards[i] = _players[i]->discardPile().size();
	}

	return discards;
}

int* GameMaster::scores() const {
	return (int *)_scores;
}

string GameMaster::roundResult() const {
	return _roundResult;
}

string GameMaster::gameWinner() const {
	vector<int> win = winners();
	// output the game winners
	stringstream ss;
	for(int i = 0; i < win.size(); i++) {
		ss	<< "Player " << win[i] << " wins!" << endl;
	}
	return ss.str();
}

void GameMaster::reset(bool resetPlayers) {
	//Resetting players
	for(int i = 0; i < PLAYER_COUNT; i++) {
		//Check if we are keeping the players and only resetting the score and their states
		if (resetPlayers==true) {
			if(_players[i] != NULL) {
				delete _players[i];
				_players[i] = NULL;
			}
			_playerTypes[i] = false;
		} else {
			if (_players[i] != NULL && _players[i]->hand().size() > 0) {
				_players[i]->returnCards();
			}
		}
		_scores[i] = 0;
	}

	_table = Table();
	_currentPlayerNumber = -1;
	_isNewRound = false;
	_isRoundOver = false;
	if(_lastCardPlayed != NULL) {
		delete _lastCardPlayed;
	}
	_lastCardPlayed = NULL;
}

void GameMaster::ragequit() {
	Player *currentPlayer = _players[_currentPlayerNumber];
	Player *computerReplacement = new ComputerPlayer(*dynamic_cast<HumanPlayer*>(currentPlayer));
	_playerTypes[_currentPlayerNumber] = true;
	_players[_currentPlayerNumber] = computerReplacement;
	takeCurrentPlayerTurn(COMPUTER_PLAYER_CARD_INDEX);
	delete currentPlayer;
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

void GameMaster::incrementPlayer() {
	if(_currentPlayerNumber == PLAYER_COUNT - 1) {
		_currentPlayerNumber = 0;
	} else {
		_currentPlayerNumber++;
	}
}
