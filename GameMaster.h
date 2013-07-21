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
	void seedDeck(int seed);
	void registerPlayers(const bool &players[4]);			//Registers a player in the game0
	Table table() const;									//Returns the table for the game
	void deal();											//Gives the players their hands from the deck
	void takeCurrentPlayerTurn();							//Executes the current player's turn
	void beginRound();										//Begins a new round of the game
	bool isGameOver() const;								//Returns true if a player has over 80 points
	std::vector<int> winners() const;						//Returns the winners of the game

	vector<Card> hand();

private:
	static const int PLAYER_COUNT = 4;
	static const int END_GAME_SCORE = 80;
	static const int INITIAL_SCORE = 0;
	Player* _players[PLAYER_COUNT];
	Deck _deck;
	Table _table;
	int _currentPlayerNumber;
	int _scores[4];
	std::vector<Card> legalMoves() const;
};

#endif