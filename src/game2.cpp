#include <iostream>
#include "WorldMap.h"
#include "WorldMapNode.h"
#include "Terrain.h"
#include "Render.h"
#include "WorldGen.h"

int main () {
    //
    WorldMap world = WorldMap(10, 10);
    render(world, std::cout);
    generate(world);
    render(world, std::cout);
    generate(world, 1u);
    render(world, std::cout);
}