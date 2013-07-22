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
		bool* playerResults() const;	//Returns the results of the check boxes in the dialog

	private:
		static const int NUMBER_OF_RESULTS = 4;
		std::vector<Gtk::CheckButton *> checkButtons;
		bool playerResults_[NUMBER_OF_RESULTS];
		Gtk::Label promptLabel;
};

#endif