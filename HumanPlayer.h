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
		class RagequitException;
};


#endif