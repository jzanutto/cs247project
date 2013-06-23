#include <iostream>
#include <sstream>
#include "Command.h"
#include "Deck.h"

using namespace std;

int main(int argc, char* argv[]) {


	Command c;
	stringstream str;
	Deck d;
	if (argc > 1) {
		str << argv[1];
		int seed;
		str >> seed;
		d = Deck(seed);
	} else {
		d = Deck();
	}
	
	while(true) {
		cin >> c;
		switch (c.type) {
			case QUIT:
				goto quit;
			case DECK:
				d.shuffle();
				cout << d;
				break;
			default:
				break;
		}
	}

quit:
	return 0;
}