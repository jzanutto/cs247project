#ifndef _STRAIGHTSWINDOW_H
#define _STRAIGHTSWINDOW_

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include "DeckUI.h"

class StraightsWindow : public Gtk::Window {
	public:
		StraightsWindow();
		virtual ~StraightsWindow();

	private:
		DeckUI deck;

		Gtk::Image *cards[13];
		Gtk::HBox hbox;
		Gtk::Frame frame;
};

#endif