CXX = g++
CXXFLAGS = -I include -std=c++17 -Wall -Wextra -MMD -MP

SRC = src/game2.cpp src/WorldMap.cpp src/WorldMapNode.cpp src/Terrain.cpp src/Render.cpp src/WorldGen.cpp
OBJ = $(SRC:src/%.cpp=build/%.o)
DEP = $(OBJ:.o=.d)

game.exe: $(OBJ)
	$(CXX) $(OBJ) -o game.exe

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f build/*.o build/*.d game.exe

-include $(DEP)
