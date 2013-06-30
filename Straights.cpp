#include <iostream>
#include <sstream>
#include <vector>
#include "Command.h"
#include "GameMaster.h"

using namespace std;

int main(int argc, char* argv[]) {	
	GameMaster *game;
	// seeding the deck
	if (argc > 1) {
		stringstream str;
		str << argv[1];
		int seed;
		str >> seed;
		game = new GameMaster(seed);
	} else {
		game = new GameMaster(0);
	}
	
	// scanning player input
	for(int i = 0; i < 4; i++) {
		cout << "Is player " << i + 1 << " a human(h) or a computer(c)?" << endl;
		cout << ">";
		char input;
		cin >> input;
		game->registerPlayer(input, i);
	}

	// while the game is not over, deal
	while(!game->isGameOver()) {
		game->deal();

		try {
			// attempt to play a round.  quitting throws an exception
			game->beginRound();	
		} catch (const char* e) {
			delete game;
			return 0;
		}		
	}

	vector<int> winners = game->winners();
	// output the game winners
	for(int i = 0; i < winners.size(); i++) {
		cout << "Player " << winners[i] << " wins!" << endl;
	}

	delete game;
	return 0;
}