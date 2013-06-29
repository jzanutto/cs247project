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

	game->deal();

	Command c;

	while(true) {
		cout << "A new round begins. It's player " 
		 << (game->currentPlayerNumber() + 1)
		 << "'s turn to play."
		 << endl;
		Player *currentPlayer = game->getPlayer(game->currentPlayerNumber());
		currentPlayer->printHand();

		cin >> c;
		switch (c.type) {
			case QUIT:
				goto quit;
			case DECK:
				cout << game->deck();
				break;
			default:
				break;
		}
	}

quit:
	delete game;
	return 0;
}