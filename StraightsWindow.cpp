#include "StraightsWindow.h"

StraightsWindow::StraightsWindow() : hbox(true, 10) {
	const Glib::RefPtr<Gdk::Pixbuf> blankCardPixBuf = deck.getBlankCardImage();
	const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = deck.getCardImage(SPADE, ACE);
	const Glib::RefPtr<Gdk::Pixbuf> otherCardPixbuf = deck.getCardImage(DIAMOND, SEVEN);


	set_border_width(10);

	frame.set_label("Cards:");
	frame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP);
	frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
	add(frame);

	frame.add(hbox);

	for(int i = 0; i < 13; i++) {
		int a = i % 3;
		switch(a) {
			case 0:
				cards[i] = new Gtk::Image(cardPixbuf);
				break;
			case 1:
				cards[i] = new Gtk::Image(otherCardPixbuf);
				break;
			default:
				cards[i] = new Gtk::Image(blankCardPixBuf);
				break;
		}
		hbox.add(*cards[i]);
	}

	show_all();
}

StraightsWindow::~StraightsWindow() { 
	for(int i = 0; i < 13; i++) {
		if(cards[i] != NULL) {
			delete cards[i];
		}
	}
}