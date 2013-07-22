#include "ComputerPlayer.h"

using namespace std;

ComputerPlayer::ComputerPlayer() {}

ComputerPlayer::ComputerPlayer(const HumanPlayer &ragequitter) {
	setHand(ragequitter.hand());
	setDiscardPile(ragequitter.discardPile());
}

ComputerPlayer::~ComputerPlayer() {}

Card* ComputerPlayer::takeTurn(Table &table, const vector<Card> &legalMoves, Card *card) {
	// check if there are legal moves
	if(legalMoves.empty()) {
		Card cardToDiscard = hand()[0];
		discardCard(cardToDiscard);
		return NULL;
	} else {
		Card cardToPlay = legalMoves[0]; 
		table.placeCard(playCard(cardToPlay));
		*card = cardToPlay;
		return card;
	}
}