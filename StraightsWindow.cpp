#include "StraightsWindow.h"
#include "ConfigurationDialogBox.h"
#include "StraightsController.h"
#include "GameMaster.h"
#include "MessageDialogBox.h"

#include <string>
#include <sstream>
#include <sigc++/sigc++.h>
#include <iostream>

StraightsWindow::StraightsWindow(GameMaster *model, StraightsController *controller) : outerTable(4), menuHBox(true, 2), startGameButton("Start New Game"), endGameButton("End Current Game")
									, cardTable(4, 13, true), playerHBox(true, 2), handHBox(true, 2), _model(model), _controller(controller) {
	
	_model->subscribe(this);
	set_title("Straights");
	set_border_width(5);

	outerTable.set_row_spacings(5);

	seedEntry.set_text("0");

	startGameButton.signal_clicked().connect(sigc::mem_fun(*this, &StraightsWindow::onStartClicked));
	endGameButton.signal_clicked().connect(sigc::mem_fun(*this, &StraightsWindow::onEndGameClicked));


	menuHBox.add(startGameButton);
	menuHBox.add(seedEntry);
	menuHBox.add(endGameButton);

	outerTable.attach(menuHBox, 0, 1, 0, 1);

	cardFrame.set_label("Table");
	cardFrame.set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
	cardFrame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

	cardTable.set_col_spacings(1);
	cardTable.set_row_spacings(2);

	for(Rank r = ACE; r < RANK_COUNT; r++) {
		clubs[r] = new Gtk::Image(deck.getBlankCardImage());
		cardTable.attach(*clubs[r], r, r+1, CLUB, CLUB+1);
		diamonds[r] = new Gtk::Image(deck.getBlankCardImage());
		cardTable.attach(*diamonds[r], r, r+1, DIAMOND, DIAMOND+1);
		hearts[r] = new Gtk::Image(deck.getBlankCardImage());
		cardTable.attach(*hearts[r], r, r+1, HEART, HEART+1);
		spades[r] = new Gtk::Image(deck.getBlankCardImage());
		cardTable.attach(*spades[r], r, r+1, SPADE, SPADE+1);
	}

	cardFrame.add(cardTable);

	for (int i = 0; i < 4; i++) {
		playerFrames[i].getRageButton().signal_clicked().connect(sigc::mem_fun(*this, &StraightsWindow::onRageClicked));
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
		handButton[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &StraightsWindow::onCardClicked), i));
		handHBox.add(handButton[i]);
	}

	handFrame.add(handHBox);

	outerTable.attach(playerHBox, 0, 1, 2, 3);
	outerTable.attach(cardFrame, 0, 1, 1, 2);
	outerTable.attach(handFrame, 0, 1, 3, 4);
	add(outerTable);

	show_all();
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

void StraightsWindow::update() {
	std::vector<Card> playerHand = _model->hand();

	for(int i = 0; i < playerHand.size(); i++) {
		Card c = playerHand[i];
		hand[i]->set(deck.getCardImage(c.getSuit(), c.getRank()));		
	}

	for(int i = playerHand.size(); i < 13; i++) {
		hand[i]->set(deck.getBlankCardImage());
	}

	Card *lastCardPlayed = _model->lastCardPlayed();
	if(lastCardPlayed != NULL) {
		Suit suit = lastCardPlayed->getSuit();
		Rank rank = lastCardPlayed->getRank();
		switch(suit) {
			case CLUB:
				clubs[rank]->set(deck.getCardImage(suit, rank));
				break;
			case DIAMOND:
				diamonds[rank]->set(deck.getCardImage(suit, rank));
				break;
			case HEART:
				hearts[rank]->set(deck.getCardImage(suit, rank));
				break;
			case SPADE:
				spades[rank]->set(deck.getCardImage(suit, rank));
				break;
		}
	} else {
		std::vector<int> discards = _model->numberOfDiscards();
		for(int i = 0; i < 4; i++) {
			std::stringstream ss;
			ss << discards[i];
			playerFrames[i].setDiscards(ss.str());
		}
	}

	int currentPlayerNumber = _model->currentPlayer();

	for(int i = 0; i < 4; i++) {
		playerFrames[i].setActive(i == currentPlayerNumber);
	}

	if(_model->isRoundOver()) {
		MessageDialogBox dialog(*this, "Round Result", _model->roundResult());

		int* scores = _model->scores();
		for(int i = 0; i < 4; i++) {
			std::stringstream ss;
			ss << scores[i];
			playerFrames[i].setPoints(ss.str());
		}
		if (_model->isGameOver()) {
			MessageDialogBox dialog(*this, "Game Over!", _model->gameWinner());
			for(int i = 0; i < 4; i++) {
				playerFrames[i].setPoints("0");
			}
		}
		reset();		
	} else if(_model->isNewRound()) {
		std::stringstream ss;
		ss << "A new round begins! It's Player ";
		ss << currentPlayerNumber + 1;
		ss << "'s turn to play!";
		MessageDialogBox dialog(*this, "New Round!", ss.str());
	}	
}

void StraightsWindow::onStartClicked() {
	ConfigurationDialogBox dialog(*this, "Choose Players");
	bool *results = dialog.playerResults();
	int seed;
	std::stringstream ss(seedEntry.get_text());
	ss >> seed;
	if (ss.fail()) {
		ss.clear();
		seed = 0;
	}

	_controller->startGameButtonClicked(seed, results);
}

void StraightsWindow::onCardClicked(int index) {
	_controller->cardClicked(index);
}

void StraightsWindow::onRageClicked() {
	_controller->rageButtonClicked();
}

void StraightsWindow::onEndGameClicked() {
	for(int i = 0; i < 4; i++) {
		playerFrames[i].setPoints("0");
	}
	reset();
	_controller->endGameButtonClicked();
}

void StraightsWindow::reset() {
	for(Rank r = ACE; r < RANK_COUNT; r++) {
		clubs[r]->set(deck.getBlankCardImage());
		diamonds[r]->set(deck.getBlankCardImage());
		hearts[r]->set(deck.getBlankCardImage());
		spades[r]->set(deck.getBlankCardImage());
		hand[r]->set(deck.getBlankCardImage());
	}
	for (int i = 0; i < 4; i++) {
		playerFrames[i].setDiscards("0");
		playerFrames[i].setActive(false);
	}
}