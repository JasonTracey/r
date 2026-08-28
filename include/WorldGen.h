#pragma once

namespace world {
    class Map;

    // generate function
    void generate(Map& w, unsigned int seed = 42u);
    void generate_value(Map& w, int spacing = 10, unsigned int seed = 1u);
    void generate_heightmap(Map& w, int spacing, unsigned int seed = 5u);
}