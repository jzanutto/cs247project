#ifndef _SmartComputerPlayerPLAYER_
#define _SmartComputerPlayerPLAYER_

#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <vector>

class SmartComputerPlayer : public ComputerPlayer {
	public:
		SmartComputerPlayer();
		SmartComputerPlayer(const HumanPlayer &ragequitter);
		virtual ~SmartComputerPlayer();
		virtual Card* takeTurn(Table &table, const std::vector<Card> &legalMoves, Card *card);
};

#endif