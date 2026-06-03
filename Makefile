game: game.o Unit.o Location.o
	g++ game.o Unit.o Location.o -o game

game.o: game.cpp Unit.h Location.h
	g++ -c game.cpp -o game.o

Location.o: Location.cpp Unit.h Location.h
	g++ -c Location.cpp -o Location.o

Unit.o: Unit.cpp Unit.h Location.h
	g++ -c Unit.cpp -o Unit.o