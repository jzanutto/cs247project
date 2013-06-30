#include <vector>
#include <algorithm>
#include "HumanPlayer.h"
#include "Command.h"

using namespace std;

class HumanPlayer::RagequitException : public exception {
	public:	
		RagequitException(char* message);
		~RagequitException() throw();
		virtual const char* what() const throw();
	private:
		char *_errorMessage;
};

HumanPlayer::HumanPlayer() {}

Card HumanPlayer::takeTurn(Table &table, const Deck &deck, const vector<Card> &legalMoves) {
	cout << table;
	printHand();

	cout << "Legal plays: ";
	for(int i = 0; i < legalMoves.size(); i++) {
		cout << legalMoves[i];
		if(i < legalMoves.size() - 1) {
			cout << " ";
		}
	}

	cout << endl;
	
	bool isValid = false;
	Card returningCard = Card(SPADE, ACE);
	while(!isValid) {
		isValid = true;
		Command c;
		cout << ">";
		cin >> c;
		
		switch (c.type) {
			case PLAY:
				if(legalMoves.empty() || legalMoves.find(c.card) == legalMoves.end()) {
					cout << "That is not a legal play." << endl;
					isValid = false;
				} else {
					try {
						table.placeCard(playCard(c.card));
						returningCard = c.card;
					} catch (const char* e) {
						cout << e << endl;
						isValid = false;
					}	
				}
				break;
			case DISCARD:
				if(!legalMoves.empty()) {
					cout << "You have a legal play. You may not discard." << endl;
					isValid = false;
				} else {
					try {
						discardCard(c.card);
						returningCard = c.card;
					} catch (const char* e) {
						cout << e << endl;
						isValid = false;
					}
				}
				break;
			case QUIT:
				throw "Game Ended";
				break;
			case DECK:
				cout << deck;
				isValid = false;
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

HumanPlayer::RagequitException::RagequitException(char* message) : _errorMessage(message) {}

HumanPlayer::RagequitException::~RagequitException() throw() {}

const char* HumanPlayer::RagequitException::what() const throw() {
	return _errorMessage;
}