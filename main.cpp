#include "StraightsWindow.h"
#include <gtkmm/main.h>

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	StraightsWindow window;
	Gtk::Main::run(window);

	return 0;
}