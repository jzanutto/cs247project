#ifndef _GAMEMASTER_
#define _GAMEMASTER_

#include "Player.h"
#include "Deck.h"

class GameMaster {
public:
	GameMaster();
	GameMaster(int seed);
	~GameMaster();
	void registerPlayer(char playerType, int playerNum);
	Deck deck() const;
	void deal();
	int currentPlayerNumber() const;
	Player* getPlayer(const int playerNumber) const;

private:
	static const int PLAYER_COUNT = 4;
	Player* _players[PLAYER_COUNT];
	Deck _deck;
	int _startingPlayerNumber;
	int _currentPlayerNumber;
};

#endif