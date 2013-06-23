#include "GameMaster.h"

using namespace std;

static GameMaster GameMaster::getInstance() {
	return instance;
}
static void GameMaster::registerPlayer(Player p, int playerNum) {
	if (playerNum <= PLAYER_COUNT) {
		_players[playerNum-1] = p;
	}
}

GameMaster::GameMaster() {
	init();
}
static void GameMaster::init();