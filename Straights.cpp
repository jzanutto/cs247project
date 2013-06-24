#include <iostream>
#include <sstream>
#include <vector>
#include "Command.h"
#include "GameMaster.h"

using namespace std;

void printPlayerHand(Player *p) {
	cout << "Your hand: ";
	vector<Card> cards = p->hand();
	for(int i = 0; i < cards.size(); i++) {
		cout << cards[i];
		if(i < cards.size() - 1) {
			cout << " ";
		}
	}

	cout << endl;
}

int main(int argc, char* argv[]) {	
	GameMaster game;
	if (argc > 1) {
		stringstream str;
		str << argv[1];
		int seed;
		str >> seed;
		game = GameMaster(seed);
	} else {
		game = GameMaster();
	}
	
	game.deal();

	cout << "A new round begins. It's player " 
		 << game.currentPlayerNumber()
		 << "'s turn to play."
		 << endl;

	Command c;

	while(true) {
		cin >> c;
		switch (c.type) {
			case QUIT:
				goto quit;
			case DECK:
				cout << game.deck();
				break;
			default:
				break;
		}
	}

quit:
	return 0;
}