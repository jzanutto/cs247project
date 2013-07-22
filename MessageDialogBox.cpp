#include "MessageDialogBox.h"
#include <gtkmm/stock.h>

using std::string;

MessageDialogBox::MessageDialogBox(Gtk::Window &parent, string title, string text) : Dialog(title, parent), messageLabel(text, Gtk::ALIGN_LEFT) {
	Gtk::VBox* contentArea = this->get_vbox();

	contentArea->add(messageLabel);

	Gtk::Button *okButton = add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all_children();

	run();
}

MessageDialogBox::~MessageDialogBox() { }