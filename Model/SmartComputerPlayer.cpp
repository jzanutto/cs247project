#include "SmartComputerPlayer.h"

SmartComputerPlayer::SmartComputerPlayer() {}

SmartComputerPlayer::SmartComputerPlayer(const HumanPlayer &ragequitter) {
	setHand(ragequitter.hand());
	setDiscardPile(ragequitter.discardPile());
}

Card* SmartComputerPlayer::takeTurn(Table &table, const std::vector<Card> &legalMoves, Card *card) {
	if (legalMoves.empty()) {
		Card bestDiscard = hand()[0];
		for (int i = 0; i < hand().size(); i++) {
			if (hand()[i].getRank() < bestDiscard.getRank()) {
				bestDiscard = hand()[i];		
			}
		}
		discardCard(bestDiscard);
		return NULL;
	} else {
		Card bestPlay = legalMoves[0];
		for (int i = 0; i < legalMoves.size(); i++) {
			if (legalMoves[i].getRank() > bestPlay.getRank()) {
				bestPlay = legalMoves[i];		
			}
		}
		table.placeCard(playCard(bestPlay));
		*card = bestPlay;
		return card;
	}

}

SmartComputerPlayer::~SmartComputerPlayer() {}
