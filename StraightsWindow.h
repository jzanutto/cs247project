#ifndef _STRAIGHTSWINDOW_H
#define _STRAIGHTSWINDOW_

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>
#include <gtkmm/entry.h>
#include "PlayerFrame.h"
#include "DeckUI.h"
#include "Observer.h"

class GameMaster;
class StraightsController;

// THIS IS THE VIEW
class StraightsWindow : public Gtk::Window, public Observer {
	public:
		StraightsWindow(GameMaster*, StraightsController*);
		virtual ~StraightsWindow();
		virtual void update();

	protected:
		virtual void onStartClicked();
		virtual void onCardClicked(int index);
		virtual void onRageClicked();
		virtual void onEndGameClicked();

	private:
		DeckUI deck;

		Gtk::Table outerTable;

		Gtk::HBox menuHBox;
		Gtk::Button startGameButton;
		Gtk::Button endGameButton;
		Gtk::Entry seedEntry;
		
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

		GameMaster *_model;
		StraightsController *_controller;

		void reset();
};

#endif