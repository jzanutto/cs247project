#ifndef _PLAYERFRAME_
#define _PLAYERFRAME_

#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <string>

class PlayerFrame : public Gtk::Frame {
	public:
		PlayerFrame();
		~PlayerFrame();
		void setPoints(std::string points);
		void setDiscards(std::string discards);
		void setActive(bool active);
		Gtk::Button& getRageButton();
	private:
		Gtk::VBox playerInfoVBox;
		Gtk::Button rageButton;
		Gtk::Label pointsLabel;
		Gtk::Label discardLabel;
};

#endif