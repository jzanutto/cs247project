#include "StraightsWindow.h"
#include <sstream>

StraightsWindow::StraightsWindow() : outerTable(4), menuHBox(true, 2), startGameButton("Start New Game"), endGameButton("End Current Game")
									, cardTable(4, 13, true), playerHBox(true, 2), handHBox(true, 2) {
	
	set_title("Straights");
	set_border_width(5);

	outerTable.set_row_spacings(5);

	menuHBox.add(startGameButton);
	menuHBox.add(endGameButton);

	outerTable.attach(menuHBox, 0, 1, 0, 1);



	cardFrame.set_label("Table");
	cardFrame.set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
	cardFrame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

	cardTable.set_col_spacings(1);
	cardTable.set_row_spacings(2);

	for(Rank r = ACE; r < RANK_COUNT; r++) {
		clubs[r] = new Gtk::Image(deck.getCardImage(CLUB, r));
		cardTable.attach(*clubs[r], r, r+1, CLUB, CLUB+1);
		diamonds[r] = new Gtk::Image(deck.getCardImage(DIAMOND, r));
		cardTable.attach(*diamonds[r], r, r+1, DIAMOND, DIAMOND+1);
		hearts[r] = new Gtk::Image(deck.getCardImage(HEART, r));
		cardTable.attach(*hearts[r], r, r+1, HEART, HEART+1);
		spades[r] = new Gtk::Image(deck.getCardImage(SPADE, r));
		cardTable.attach(*spades[r], r, r+1, SPADE, SPADE+1);
	}

	cardFrame.add(cardTable);

	for (int i = 0; i < 4; i++) {
		std::stringstream stream;
		stream << (1 + i);
		std::string name = "Player " + stream.str();
		playerFrames[i].set_label(name);
		playerHBox.add(playerFrames[i]);
	}



	handFrame.set_label("Your hand");
	handFrame.set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
	handFrame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

	for (int i = 0; i < 13; i++) {
		hand[i] = new Gtk::Image(deck.getBlankCardImage());
		handButton[i].set_image(*hand[i]);
		handHBox.add(handButton[i]);
	}

	handFrame.add(handHBox);

	outerTable.attach(playerHBox, 0, 1, 2, 3);
	outerTable.attach(cardFrame, 0, 1, 1, 2);
	outerTable.attach(handFrame, 0, 1, 3, 4);
	add(outerTable);

	show_all();

	/*const Glib::RefPtr<Gdk::Pixbuf> blankCardPixBuf = deck.getBlankCardImage();
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

	show_all();*/
}

StraightsWindow::~StraightsWindow() { 
	for(int i = 0; i < 13; i++) {
		
		if(clubs[i] != NULL) {
			delete clubs[i];
		}

		if(diamonds[i] != NULL) {
			delete diamonds[i];
		}

		if(hearts[i] != NULL) {
			delete hearts[i];
		}

		if(spades[i] != NULL) {
			delete spades[i];
		}

		if(hand[i] != NULL) {
			delete hand[i];
		}
	}
}