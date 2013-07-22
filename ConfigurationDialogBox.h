#ifndef _CONFIGURATIONDIALOGBOX_
#define _CONFIGURATIONDIALOGBOX_

#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/entry.h>
#include <string>
#include <vector>

class ConfigurationDialogBox : public Gtk::Dialog {
	public:
		ConfigurationDialogBox(Gtk::Window &parent, std::string title);
		virtual ~ConfigurationDialogBox();
		bool* playerResults() const;

	private:
		std::vector<Gtk::CheckButton *> checkButtons;
		bool playerResults_[4];
		Gtk::Label promptLabel;
};

#endif