CXX = g++
CXXFLAGS = -I include -std=c++17 -Wall -Wextra -MMD -MP

SRC = src/game2.cpp src/WorldMap.cpp src/WorldMapNode.cpp src/Terrain.cpp src/Render.cpp src/WorldGen.cpp src/Lattice.cpp
OBJ = $(SRC:src/%.cpp=build/%.o)
DEP = $(OBJ:.o=.d)

game.exe: $(OBJ)
	$(CXX) $(OBJ) -o game.exe

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Diagnose a silent "ld returned 1 exit status" - see tools/linkcheck.sh
linkcheck:
	@sh tools/linkcheck.sh build

clean:
	rm -f build/*.o build/*.d game.exe

.PHONY: linkcheck clean

-include $(DEP)
