#include "WorldMapNode.h"
#include <stdexcept>

WorldMapNode::WorldMapNode(Coord pos) : pos_(pos), terrain_(Terrain::Soil) {}
void WorldMapNode::set_terrain(Terrain terrain) {
    if (terrain >= Terrain::Count) {
        throw std::out_of_range("set_terrain terrain out of range");
    }
    terrain_ = terrain;
}