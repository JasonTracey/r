#pragma once
#include <iostream>
#include <string>

namespace world {
    // pre
    class Map;

    // render function
    void render(const Map& w, std::ostream& out = std::cout);
    void render_height(const Map& w, std::ostream& out = std::cout);
    void render_height_to_pgm(const Map& w, std::string filename);
}