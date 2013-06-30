#include <iostream>
#include <sstream>
#include <vector>
#include "Command.h"
#include "GameMaster.h"

using namespace std;

int main(int argc, char* argv[]) {	
	GameMaster *game;
	if (argc > 1) {
		stringstream str;
		str << argv[1];
		int seed;
		str >> seed;
		game = new GameMaster(seed);
	} else {
		game = new GameMaster();
	}
	
	for(int i = 0; i < 4; i++) {
		game->registerPlayer('h', i);
	}

	while(!game->isGameOver()) {
		game->deal();

		try {
			game->beginRound();	
		} catch (const char* e) {
			delete game;
			return 0;
		}		
	}

	vector<int> winners = game->winners();

	for(int i = 0; i < winners.size(); i++) {
		cout << "Player " << winners[i] << " wins!" << endl;
	}

	delete game;
	return 0;
}