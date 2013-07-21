#include "PlayerFrame.h"

using std::string;

PlayerFrame::PlayerFrame() : playerInfoVBox(true, 1),
							rageButton("Rage! >:("),
							pointsLabel("0 points", Gtk::ALIGN_CENTER),
							discardLabel("0 discards", Gtk::ALIGN_CENTER) {

	set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP);
	set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
	
	rageButton.set_sensitive(false);
	
	playerInfoVBox.add(rageButton);
	playerInfoVBox.add(pointsLabel);
	playerInfoVBox.add(discardLabel);

	add(playerInfoVBox);
}
PlayerFrame::~PlayerFrame() {}

void PlayerFrame::setPoints(string points) {
	string label = points + " points";
	discardLabel.set_label(label);
}

void PlayerFrame::setDiscards(string discardCount) {
	string label = discardCount + " discards";
	discardLabel.set_label(label);
}

void PlayerFrame::setActive(bool active) {
	rageButton.set_sensitive(active);
}
