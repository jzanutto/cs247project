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
	void takeCurrentPlayerTurn();
	void beginRound();
	bool isGameOver() const;
	std::vector<int> winners() const;
	int currentPlayerNumber() const;
	Player* getPlayer(const int playerNumber) const;
private:
	static const int PLAYER_COUNT = 4;
	Player* _players[PLAYER_COUNT];
	Deck _deck;
	Table _table;
	int _currentPlayerNumber;
	int _scores[4];
	std::vector<Card> legalMoves() const;
	void init();
};

#endif