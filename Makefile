CXX = clang++
# variables and initialization
CXXFLAGS = -g -Wall -MMD `pkg-config gtkmm-2.4 --cflags --libs`
# builds dependency lists in .d files
OBJECTS = StraightsWindow.o DeckUI.o main.o
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
