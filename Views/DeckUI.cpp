#include "DeckUI.h"
#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>

using namespace std;

const char *imageNames[] = {
	"img/0_0.png",
	"img/0_1.png",
	"img/0_2.png",
	"img/0_3.png",
	"img/0_4.png",
	"img/0_5.png",
	"img/0_6.png",
	"img/0_7.png",
	"img/0_8.png",
	"img/0_9.png",
	"img/0_j.png",
	"img/0_q.png",
	"img/0_k.png",
	"img/1_0.png",
	"img/1_1.png",
	"img/1_2.png",
	"img/1_3.png",
	"img/1_4.png",
	"img/1_5.png",
	"img/1_6.png",
	"img/1_7.png",
	"img/1_8.png",
	"img/1_9.png",
	"img/1_j.png",
	"img/1_q.png",
	"img/1_k.png",
	"img/2_0.png",
	"img/2_1.png",
	"img/2_2.png",
	"img/2_3.png",
	"img/2_4.png",
	"img/2_5.png",
	"img/2_6.png",
	"img/2_7.png",
	"img/2_8.png",
	"img/2_9.png",
	"img/2_j.png",
	"img/2_q.png",
	"img/2_k.png",
	"img/3_0.png",
	"img/3_1.png",
	"img/3_2.png",
	"img/3_3.png",
	"img/3_4.png",
	"img/3_5.png",
	"img/3_6.png",
	"img/3_7.png",
	"img/3_8.png",
	"img/3_9.png",
	"img/3_j.png",
	"img/3_q.png",
	"img/3_k.png",
	"img/nothing.png"
};

Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string &name) {
	return Gdk::Pixbuf::create_from_file(name);
}

DeckUI::DeckUI() {
	transform(&imageNames[0], &imageNames[G_N_ELEMENTS(imageNames)], 
		std::back_inserter(cardImages), &createPixbuf);
}

DeckUI::~DeckUI() { }

Glib::RefPtr<Gdk::Pixbuf> DeckUI::getCardImage(Suit suit, Rank rank) {
	int index = suit*13 + rank;
	return cardImages[index];
}

Glib::RefPtr<Gdk::Pixbuf> DeckUI::getBlankCardImage() {
	int size = cardImages.size();
	return cardImages[size - 1];
}