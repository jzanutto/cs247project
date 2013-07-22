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
		//Click listeners for buttons
		virtual void onStartClicked();
		virtual void onCardClicked(int index);
		virtual void onRageClicked();
		virtual void onEndGameClicked();

	private:
		static const int NUMBER_OF_CARDS_IN_ROW = 13;
		static const int NUMBER_OF_PLAYERS = 4;
		DeckUI deck;

		Gtk::Table outerTable;

		//Top Row
		Gtk::HBox menuHBox;
		Gtk::Button startGameButton;
		Gtk::Button endGameButton;
		Gtk::Entry seedEntry;
		
		//Card Table Display
		Gtk::Frame cardFrame;
		Gtk::Table cardTable;
		Gtk::Image *clubs[NUMBER_OF_CARDS_IN_ROW];
		Gtk::Image *diamonds[NUMBER_OF_CARDS_IN_ROW];
		Gtk::Image *hearts[NUMBER_OF_CARDS_IN_ROW];
		Gtk::Image *spades[NUMBER_OF_CARDS_IN_ROW];
		
		//Player Views
		PlayerFrame playerFrames[NUMBER_OF_PLAYERS];
		Gtk::HBox playerHBox;		

		//Hand
		Gtk::Frame handFrame;
		Gtk::HBox handHBox;
		Gtk::Button handButton[NUMBER_OF_CARDS_IN_ROW];
		Gtk::Image *hand[NUMBER_OF_CARDS_IN_ROW];

		//Model/Controller
		GameMaster *_model;
		StraightsController *_controller;

		void reset();
};

#endif