#ifndef _MESSAGEDIALOGBOX_
#define _MESSAGEDIALOGBOX_

#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <string>

class MessageDialogBox : public Gtk::Dialog {
	public:
		MessageDialogBox(Gtk::Window &parent, std::string title, std::string text);
		virtual ~MessageDialogBox();

	private:
		Gtk::Label messageLabel;
};

#endif