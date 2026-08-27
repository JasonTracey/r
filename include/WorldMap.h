#pragma once
#include <vector>
#include "WorldMapNode.h"

// Class
class WorldMap {
    public:
        WorldMap(
            int width,
            int height
        );
        ~WorldMap() = default;

        const std::vector<WorldMapNode>& nodes() const {return nodes_;}
        int width() const {return width_;}
        int height() const {return height_;}
        int size() const {return size_;}

        const WorldMapNode& node_at(Coord c) const;
        WorldMapNode& node_at(Coord c);
    private:
        int width_, height_, size_;
        int index(Coord c) const {return width_*c.y+c.x;}
        bool coord_inbounds(Coord c) const;
        std::vector<WorldMapNode> nodes_;
};