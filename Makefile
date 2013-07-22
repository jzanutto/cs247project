CXX = clang++
# variables and initialization
CXXFLAGS = -g -Wall -MMD `pkg-config gtkmm-2.4 --cflags --libs`
# builds dependency lists in .d files
OBJECTS = Views/StraightsWindow.o Views/DeckUI.o main.o Views/PlayerFrame.o Views/MessageDialogBox.o Views/ConfigurationDialogBox.o Model/GameMaster.o Model/Player.o Controller/StraightsController.o Common/Card.o Model/Deck.o Model/Table.o Model/Subject.o Model/HumanPlayer.o Model/SmartComputerPlayer.o Model/ComputerPlayer.o
DEPENDS = ${OBJECTS:.o=.d}
# substitute ".o" with ".d"
EXEC = straights
${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

clean : # separate target; cleans directory
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
# reads the .d files and reruns
# dependencies
