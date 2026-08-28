#include <iostream>
#include <fstream>
#include <vector>
#include "Map.h"
#include "MapNode.h"
#include "Terrain.h"
#include "Render.h"
#include "WorldGen.h"

int main () {
    //
    world::Map world = world::Map(100, 100);
    render(world, std::cout);
    generate(world);
    // render(world, std::cout);
    // generate(world, 1u);
    // render(world, std::cout);
    // generate_value(world, 10, 1u);
    // render(world, std::cout);
    // generate_value(world, 10, 42u);
    // render(world, std::cout);
    // generate_value(world, 10, 3u);
    // render(world, std::cout);
    // generate_value(world, 10, 14u);
    generate_heightmap(world, 50, 2u);
    render(world, std::cout);
    std::ofstream file("map.txt");
    render_height(world, file);
    render_height_to_pgm(world, "map");
    // generate_value(world, 5, 42u);
    // render(world, std::cout);
    // generate_value(world, 1, 42u);
    // render(world, std::cout);
    // generate_value(world, 3, 42u);
    // render(world, std::cout);

}