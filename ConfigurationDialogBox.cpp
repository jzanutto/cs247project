#include "ConfigurationDialogBox.h"
#include <sstream>
#include <gtkmm/stock.h>

using std::string;
using std::vector;

ConfigurationDialogBox::ConfigurationDialogBox(Gtk::Window &parent, string title) :  Dialog( title, parent, true, true ), promptLabel("Choose Computer Players (Optional):", Gtk::ALIGN_LEFT) {
	
	// Obtain the dialog box's vertical alignment box.
	Gtk::VBox* contentArea = this->get_vbox();

	contentArea->add(promptLabel);
	
	for (int i = 0; i < 4; i++) {
		std::stringstream ss;
		ss << (i + 1);
		string label = "Player " + ss.str();
		Gtk::CheckButton *check = new Gtk::CheckButton(label);
		checkButtons.push_back(check);
		contentArea->add(*checkButtons[i]);
	}

	// Add a standard "ok" buttons with the appropriate responses when clicked.
    Gtk::Button *okButton = add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all_children();
	
    // Wait for a response from the dialog box.
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
            for (int i = 0; i < checkButtons.size(); i++) {
            	playerResults_[i] = checkButtons[i]->get_active();
            }
            break;
        default:
        	for (int i = 0; i < 4; i++) {
            	playerResults_[i] = false;
        	}
        	break;
    } // switch    		
}

ConfigurationDialogBox::~ConfigurationDialogBox() {
	for (int i = 0; i < checkButtons.size(); i++) {
		if (checkButtons[i] != NULL) {
			delete checkButtons[i];
		}
	}
	checkButtons.clear();
} // MyDialogBox::~MyDialogBox

bool* ConfigurationDialogBox::playerResults() const {
	return (bool *)playerResults_;
}