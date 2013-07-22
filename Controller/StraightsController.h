#ifndef _STRAIGHTSCONTROLLER_
#define _STRAIGHTSCONTROLLER_

#include <gtkmm.h>

class GameMaster;

class StraightsController {
public:
   StraightsController(GameMaster *);
   void startGameButtonClicked(int seed, const bool *playerTypes, const bool hardMode);
   void endGameButtonClicked();
   void rageButtonClicked();
   void cardClicked(int index);

private:
   GameMaster *_model;
}; // Controller


#endif