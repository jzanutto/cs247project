#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"
#include "HumanPlayer.h"
#include <vector>

class ComputerPlayer : public Player {
	public:
		ComputerPlayer();
		ComputerPlayer(const HumanPlayer &ragequitter);		// constructor that copies human player attributes
		virtual ~ComputerPlayer();
		virtual Card* takeTurn(Table &table, const std::vector<Card> &legalMoves, Card *card);
};

#endif