#ifndef _STRAIGHTSWINDOW_H
#define _STRAIGHTSWINDOW_

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>
#include "PlayerFrame.h"
#include "DeckUI.h"
#include "Observer.h"


// THIS IS THE VIEW
class StraightsWindow : public Gtk::Window, public Observer {
	public:
		StraightsWindow( Controller*, Model* );
		virtual ~StraightsWindow();
		virtual void update();

	private:
		DeckUI deck;

		Gtk::Table outerTable;

		Gtk::HBox menuHBox;
		Gtk::Button startGameButton;
		Gtk::Button endGameButton;

		
		Gtk::Frame cardFrame;
		Gtk::Table cardTable;
		Gtk::Image *clubs[13];
		Gtk::Image *diamonds[13];
		Gtk::Image *hearts[13];
		Gtk::Image *spades[13];
		
		PlayerFrame playerFrames[4];
		Gtk::HBox playerHBox;		

		Gtk::Frame handFrame;
		Gtk::HBox handHBox;
		Gtk::Button handButton[13];
		Gtk::Image *hand[13];
};

#endif