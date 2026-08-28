#include <iostream>
#include <vector>
#include "WorldMap.h"
#include "WorldMapNode.h"
#include "Terrain.h"
#include "Render.h"
#include "WorldGen.h"

int main () {
    //
    WorldMap world = WorldMap(100, 100);
    // render(world, std::cout);
    // generate(world);
    // render(world, std::cout);
    // generate(world, 1u);
    // render(world, std::cout);
    // generate_value(world, 10, 1u);
    // render(world, std::cout);
    generate_value(world, 10, 42u);
    render(world, std::cout);
    generate_value(world, 10, 3u);
    render(world, std::cout);
    generate_value(world, 10, 14u);
    render(world, std::cout);
    // generate_value(world, 5, 42u);
    // render(world, std::cout);
    // generate_value(world, 1, 42u);
    // render(world, std::cout);
    // generate_value(world, 3, 42u);
    // render(world, std::cout);

}