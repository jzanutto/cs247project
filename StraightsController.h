#ifndef _STRAIGHTSCONTROLLER_
#define _STRAIGHTSCONTROLLER_


#include <gtkmm.h>

class StraightsController {
public:
   //Controller( );
   void nextButtonClicked();
   void resetButtonClicked();
   void startGameButtonClicked(int seed, const bool &playerTypes[4]);
   void endGameButtonClicked();
   void rageButtonClicked(int playerNum);
   void moveAttempted(int handPosition);
private:
   //Model *model_;
}; // Controller


#endif
