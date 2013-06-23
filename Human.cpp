#include <vector>
#include "Player.h"

using namespace std;

class Human: public Player {
public:
	Human();
	~Human() {}
	virtual Card playCard();

private:
	std::vector<Card> _hand;
	int _score;

};