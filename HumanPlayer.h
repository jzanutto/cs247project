#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <vector>
#include <exception>
#include "Player.h"

class HumanPlayer : public Player {
	public:
		HumanPlayer();
		virtual ~HumanPlayer() {}
		virtual Card takeTurn(Table &table, const Deck &deck, const std::vector<Card> &legalMoves);
		class RagequitException;			// class exception object called when player ragequits
		class QuitGameException;			// class exception object called when the user wants to quit the session
};


#endif