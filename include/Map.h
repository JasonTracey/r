#pragma once
#include <vector>
#include "MapNode.h"

namespace world {
// Class
    class Map {
        public:
            Map(
                int width,
                int height
            );
            ~Map() = default;

            const std::vector<MapNode>& nodes() const {return nodes_;}
            int width() const {return width_;}
            int height() const {return height_;}
            int size() const {return size_;}

            const MapNode& node_at(GridPos c) const;
            MapNode& node_at(GridPos c);
        private:
            int width_, height_, size_;
            int index(GridPos c) const {return width_*c.y+c.x;}
            bool pos_inbounds(GridPos c) const;
            std::vector<MapNode> nodes_;
    };
}