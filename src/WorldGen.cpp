
#include "WorldGen.h"
#include "Map.h"
#include "MapNode.h"
#include "Terrain.h"
#include "Lattice.h"
#include <random>

namespace world {
    void generate(Map& w, unsigned int seed) {
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

    void generate_value(Map& w, int spacing, unsigned int seed) {
        Lattice lattice = Lattice(w.width(), w.height() ,spacing,seed);
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
    void generate_heightmap(Map& w, int spacing, unsigned int seed) {
        Lattice lattice = Lattice(w.width(), w.height() ,spacing,seed);
        for (int y = 0; y < w.height(); y++) {
            for (int x = 0; x < w.width(); x++) {
                w.node_at({x, y}).set_height(
                        lattice.sample({x, y})
                );
            }
        }
    }
}