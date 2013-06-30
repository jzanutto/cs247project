CXX = clang++
# variables and initialization
CXXFLAGS = -g -Wall -MMD
# builds dependency lists in .d files
OBJECTS = Straights.o Command.o Card.o Deck.o Player.o HumanPlayer.o GameMaster.o Table.o ComputerPlayer.o
DEPENDS = ${OBJECTS:.o=.d}
# substitute ".o" with ".d"
EXEC = program
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
clean : # separate target; cleans directory
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
# reads the .d files and reruns
# dependencies
