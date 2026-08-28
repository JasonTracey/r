#include "MapNode.h"
#include "Map.h"
#include <stdexcept>

namespace world {
    MapNode::MapNode(GridPos pos) : pos_(pos), terrain_(Terrain::Soil) {}
    void MapNode::set_terrain(Terrain terrain) {
        if (terrain >= Terrain::Count) {
            throw std::out_of_range("set_terrain terrain out of range");
        }
        terrain_ = terrain;
    }
}