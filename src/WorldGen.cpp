
#include "WorldGen.h"
#include "WorldMap.h"
#include "WorldMapNode.h"
#include "Terrain.h"
#include "Lattice.h"
#include <random>

void generate(WorldMap& w, unsigned int seed) {
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(Terrain::Count)-1
    );

    for (int y = 0; y < w.height(); y++) {
        for (int x = 0; x < w.width(); x++) {
            w.node_at({x, y}).set_terrain(
                static_cast<Terrain>(distribution(generator))
            );
        }
    }
} 

void generate_value(WorldMap& w, int spacing, unsigned int seed) {
    Lattice lattice = Lattice(w,spacing,seed);
    for (int y = 0; y < w.height(); y++) {
        for (int x = 0; x < w.width(); x++) {
            w.node_at({x, y}).set_terrain(
                terrain_from_value(
                    lattice.sample({x, y})
                )
            );
        }
    }
}