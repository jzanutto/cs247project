#include "ComputerPlayer.h"

using namespace std;

ComputerPlayer::ComputerPlayer() {}

ComputerPlayer::ComputerPlayer(const HumanPlayer &ragequitter) {}

ComputerPlayer::~ComputerPlayer() {}

Card ComputerPlayer::takeTurn(Table &table, const Deck &deck, const vector<Card> &legalMoves) {
	if(legalMoves.empty()) {
		Card card = hand()[0];
		discardCard(card);
		return card;
	} else {
		table.placeCard(playCard(legalMoves[0]));
		return legalMoves[0];
	}
}