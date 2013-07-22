/*
Modified version of the DeckGUI class in the GTKMM examples from class
*/

#ifndef _DECKUI_
#define _DECKUI_

#include "../Common/Card.h"
#include <gdkmm/pixbuf.h>
#include <vector>

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