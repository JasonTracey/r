#include "WorldMap.h"
#include <stdexcept>
#include <limits>

//public
WorldMap::WorldMap(int width, int height) 
    : width_(width), height_(height)
{
    long long product = static_cast<long long>(width_) * height;
    if (width <= 0 || height <= 0) {
        throw std::out_of_range("WorldMap width and height must be positive");
    }
    if (product>std::numeric_limits<int>::max()) {
        throw std::overflow_error("WorldMap width and height product overflow");
    }
    size_= height*width;
    nodes_.reserve(width * height); // vector capacity -> size
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            nodes_.emplace_back(Coord {x, y});
        }
    }
}
bool WorldMap::coord_inbounds(Coord c) const {
    return (0 <= c.x && c.x < width_) && (0 <= c.y && c.y < height_);
}
const WorldMapNode& WorldMap::node_at(Coord c) const {
    if (coord_inbounds(c)) {
        return nodes_[index(c)];
    }
    throw std::out_of_range("node_at: coord off map");
}
WorldMapNode& WorldMap::node_at(Coord c) {
    if (coord_inbounds(c)) {
        return nodes_[index(c)];
    }
    throw std::out_of_range("node_at: coord off map");
}