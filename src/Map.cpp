#include "Map.h"
#include <stdexcept>
#include <limits>

namespace world {
    //public
    Map::Map(int width, int height) 
        : width_(width), height_(height)
    {
        long long product = static_cast<long long>(width_) * height;
        if (width <= 0 || height <= 0) {
            throw std::out_of_range("Map width and height must be positive");
        }
        if (product>std::numeric_limits<int>::max()) {
            throw std::overflow_error("Map width and height product overflow");
        }
        size_= height*width;
        nodes_.reserve(width * height); // vector capacity -> size
        for (int y=0; y<height; y++) {
            for (int x=0; x<width; x++) {
                nodes_.emplace_back(GridPos {x, y});
            }
        }
    }
    bool Map::pos_inbounds(GridPos c) const {
        return (0 <= c.x && c.x < width_) && (0 <= c.y && c.y < height_);
    }
    const MapNode& Map::node_at(GridPos c) const {
        if (pos_inbounds(c)) {
            return nodes_[index(c)];
        }
        throw std::out_of_range("node_at: Position off map");
    }
    MapNode& Map::node_at(GridPos c) {
        if (pos_inbounds(c)) {
            return nodes_[index(c)];
        }
        throw std::out_of_range("node_at: Position off map");
    }
}