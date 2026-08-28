#pragma once
#include <vector>

// pre
class WorldMap;

// generate function
void generate(WorldMap& w, unsigned int seed = 42u);
void generate_value(WorldMap& w, int spacing = 10, unsigned int seed = 1u);