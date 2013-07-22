#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <vector>
#include <exception>
#include "Player.h"

class HumanPlayer : public Player {
	public:
		HumanPlayer();
		virtual ~HumanPlayer() {}
		virtual Card* takeTurn(Table &table, const std::vector<Card> &legalMoves, Card *card);
		class RagequitException;			// class exception object called when player ragequits
		class BadMoveException;			// class exception object called when the user wants to quit the session
};


#endif