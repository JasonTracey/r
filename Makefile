CXX = g++
CXXFLAGS = -I include

SRC = src/game.cpp src/Unit.cpp src/Location.cpp
OBJ = $(SRC:src/%.cpp=build/%.o)

game: $(OBJ)
	$(CXX) $(OBJ) -o game

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f build/*.o game.exe
