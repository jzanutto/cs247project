#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"
#include "HumanPlayer.h"
#include <vector>

class ComputerPlayer : public Player {
	public:
		ComputerPlayer();
		ComputerPlayer(const HumanPlayer &ragequitter);
		virtual ~ComputerPlayer();
		virtual Card takeTurn(Table &table, const Deck &deck, const std::vector<Card> &legalMoves);
};

#endif