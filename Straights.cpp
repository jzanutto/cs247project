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
		cout << "Is player " << i + 1 << " a human(h) or a computer(c)?" << endl;
		cout << ">";
		char input;
		cin >> input;
		game->registerPlayer(input, i);
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

	cout << endl;

	delete game;
	return 0;
}