#pragma once
#include "Coord.h"
#include "Terrain.h"

class WorldMapNode {
    public:
        explicit WorldMapNode(Coord pos);
        ~WorldMapNode() = default;
        Coord pos() const {return pos_;}
        Terrain terrain() const {return terrain_;}
        int x() const {return pos_.x;}
        int y() const {return pos_.y;}
        void set_terrain(Terrain terrain);
    private:
        Coord pos_;
        Terrain terrain_;
};