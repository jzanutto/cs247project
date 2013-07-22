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

class HumanPlayer::BadMoveException : public exception {
	public:	
		BadMoveException(char* message) : _errorMessage(message) {}
		~BadMoveException() throw() {}
		virtual const char* what() const throw() { return _errorMessage; }
	private:
		char *_errorMessage;
};

HumanPlayer::HumanPlayer() {}

Card* HumanPlayer::takeTurn(Table &table, const vector<Card> &legalMoves, Card *card) {
	if(legalMoves.empty()) {
		discardCard(*card);
		return NULL;
	} else if(find(legalMoves.begin(), legalMoves.end(), *card) != legalMoves.end()) {
		table.placeCard(playCard(*card));
		return card;
	} else {
		throw BadMoveException("Not a valid move");
		return NULL;
	}
}