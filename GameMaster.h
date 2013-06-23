#ifndef _GAMEMASTER_
#define _GAMEMASTER_

#include "Player.h"
#include "Deck.h"

class GameMaster {
private:
	static void init();
	GameMaster();
	static GameMaster instance;
	static const int PLAYER_COUNT = 4;
	static Player _players[PLAYER_COUNT];

public:
	~GameMaster() {}
	static GameMaster getInstance();
	static void registerPlayer(Player p, int playerNum);


};

#endif