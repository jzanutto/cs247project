#ifndef _DECKUI_
#define _DECKUI_

#include <gdkmm/pixbuf.h>
#include <vector>

enum Suit { CLUB=0, DIAMOND=1, HEART=2, SPADE=3, SUIT_COUNT=4 };
enum Rank { ACE=0, TWO=1, THREE=2, FOUR=3, FIVE=4, SIX=5, SEVEN=6,
			EIGHT=7, NINE=8, TEN=9, JACK=10, QUEEN=11, KING=12, RANK_COUNT=13 };

class DeckUI {
	public:
		DeckUI();
		virtual ~DeckUI();
		Glib::RefPtr<Gdk::Pixbuf> getCardImage(Suit suit, Rank rank);
		Glib::RefPtr<Gdk::Pixbuf> getBlankCardImage();

	private:
		std::vector< Glib::RefPtr<Gdk::Pixbuf> > cardImages;
};

#endif