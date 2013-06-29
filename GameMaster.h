#ifndef _GAMEMASTER_
#define _GAMEMASTER_

#include <vector>
#include "Player.h"
#include "Deck.h"
#include "Table.h"

class GameMaster {
public:
	GameMaster();
	GameMaster(int seed);
	~GameMaster();
	void registerPlayer(char playerType, int playerNum);
	Deck deck() const;
	Table table() const;
	void deal();
	int currentPlayerNumber() const;
	Player* getPlayer(const int playerNumber) const;
	void printLegalMoves() const;
private:
	static const int PLAYER_COUNT = 4;
	Player* _players[PLAYER_COUNT];
	Deck _deck;
	Table _table;
	int _startingPlayerNumber;
	int _currentPlayerNumber;
	std::vector<Card> legalMoves() const;
};

#endif