#ifndef _GAMEMASTER_
#define _GAMEMASTER_

#include <vector>
#include "Player.h"
#include "Deck.h"
#include "Table.h"
#include "Subject.h"

// THIS IS THE MODEL
class GameMaster : public Subject {
public:
	GameMaster();											//Constructor for randomly seeded deck
	~GameMaster();
	void seedDeck(int seed);								//Seeds the random number generator for the deck with seed
	void registerPlayers(const bool *players);			//Registers a player in the game0
	Table table() const;									//Returns the table for the game
	void deal();											//Gives the players their hands from the deck
	void takeCurrentPlayerTurn(int cardIndex);				//Executes the current player's turn
	void beginRound();										//Begins a new round of the game
	bool isGameOver() const;								//Returns true if a player has over 80 points
	std::vector<Card> hand() const;							//Returns the current player's hand
	bool isNewRound();										//Returns whether a new round has started, value is reset to false afterward
	bool isRoundOver();										//Returns whether a round is over, value is reset to false afterward.
	int currentPlayer() const;								//Returns the current player number
	Card* lastCardPlayed() const;							//Returns the last card played on the table, NULL if the last move was a discard
	std::vector<int> numberOfDiscards() const;				//Returns the number of discards for all players
	int* scores() const;									//Returns the scores for all players
	std::string roundResult() const;						//Returns a string with the results of the round
	std::string gameWinner() const;							//Returns a string with the winners of the game
	void reset(bool resetPlayers=true);						//Resets the state of the mode, if false is passed, ignores resetting players
	void ragequit();										//Converts the current player into a computer and plays their turn

private:
	static const int PLAYER_COUNT = 4;
	static const int END_GAME_SCORE = 80;
	static const int INITIAL_SCORE = 0;
	static const int COMPUTER_PLAYER_CARD_INDEX = -1;
	static const bool HUMAN = false;
	Player* _players[PLAYER_COUNT];
	Deck _deck;
	Table _table;
	int _currentPlayerNumber;
	int _scores[4];
	bool _playerTypes[4];
	bool _isNewRound;
	bool _isRoundOver;
	Card *_lastCardPlayed;
	std::vector<Card> legalMoves() const;					
	std::string _roundResult;
	std::vector<int> winners() const;
	void incrementPlayer();					
};

#endif