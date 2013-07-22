#ifndef _CARD_
#define _CARD_

#include <ostream>
#include <istream>

enum Suit { CLUB=0, DIAMOND=1, HEART=2, SPADE=3, SUIT_COUNT=4 };
enum Rank { ACE=0, TWO=1, THREE=2, FOUR=3, FIVE=4, SIX=5, SEVEN=6,
			EIGHT=7, NINE=8, TEN=9, JACK=10, QUEEN=11, KING=12, RANK_COUNT=13 };

class Card{
	friend std::istream &operator>>(std::istream &, Card &);

public:
	Card(Suit, Rank);
	Suit getSuit() const;
	Rank getRank() const;
	
private:
	Suit suit_;
	Rank rank_;
};

bool operator==(const Card &, const Card &);

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

#endif
