#include <vector>
#include <algorithm>
#include "HumanPlayer.h"
#include "Command.h"

using namespace std;

class HumanPlayer::RagequitException : public exception {
	public:	
		RagequitException(char* message) : _errorMessage(message) {}
		~RagequitException() throw() {}
		virtual const char* what() const throw() { return _errorMessage; }
	private:
		char *_errorMessage;
};

class HumanPlayer::QuitGameException : public exception {
	public:	
		QuitGameException(char* message) : _errorMessage(message) {}
		~QuitGameException() throw() {}
		virtual const char* what() const throw() { return _errorMessage; }
	private:
		char *_errorMessage;
};

HumanPlayer::HumanPlayer() {}

Card HumanPlayer::takeTurn(Table &table, const Deck &deck, const vector<Card> &legalMoves) {
	cout << table;
	printHand();
	// outputs the legal plays for the user
	cout << "Legal plays: ";
	for(int i = 0; i < legalMoves.size(); i++) {
		cout << legalMoves[i];
		if(i < legalMoves.size() - 1) {
			cout << " ";
		}
	}

	cout << endl;
	
	bool isLegal = false;
	Card returningCard = Card(SPADE, ACE);
	// expects legality in loop
	while(!isLegal) {
		isLegal = true;
		Command c;
		cout << ">";
		cin >> c;
		// reading in commands
		switch (c.type) {
			case PLAY:
				if(legalMoves.empty() || find(legalMoves.begin(), legalMoves.end(), c.card) == legalMoves.end()) {
					cout << "That is not a legal play." << endl;
					isLegal = false;
				} else {
					try {
						table.placeCard(playCard(c.card));
						returningCard = c.card;
					} catch (const char* e) {
						cout << e << endl;
						isLegal = false;
					}	
				}
				break;
			case DISCARD:
				if(!legalMoves.empty()) {
					cout << "You have a legal play. You may not discard." << endl;
					isLegal = false;
				} else {
					try {
						discardCard(c.card);
						returningCard = c.card;
					} catch (const char* e) {
						cout << e << endl;
						isLegal = false;
					}
				}
				break;
			case QUIT:
				throw QuitGameException("Game ending :(");
				break;
			case DECK:
				cout << deck;
				isLegal = false;
				break;
			case RAGEQUIT:
				throw RagequitException("This player ragequit");
				break;
			default:
				break;
		}	
	}	
	return returningCard;
}