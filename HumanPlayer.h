#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <vector>
#include "Player.h"

class HumanPlayer: public Player {
public:
	HumanPlayer();
	virtual ~HumanPlayer() {}
	virtual void takeTurn();
};


#endif