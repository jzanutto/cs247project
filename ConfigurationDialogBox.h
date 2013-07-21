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
		ConfigurationDialogBox(Gtk::Window &parent, string title);
		virtual ~ConfigurationDialogBox();
		std::vector<bool> playerResults() const;
		int seedValue() const;

	private:
		std::vector<Gtk::CheckButton *> radioButtons;
		std::vector<bool> playerResults_;
		int seedValue_;
};

#endif