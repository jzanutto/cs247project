#include "Views/StraightsWindow.h"
#include <gtkmm/main.h>
#include "Model/GameMaster.h"
#include "Controller/StraightsController.h"

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	GameMaster model;                          // Create model
    StraightsController controller(&model);  // Create controller
	StraightsWindow view(&model, &controller);   
	Gtk::Main::run(view);

	return 0;
}