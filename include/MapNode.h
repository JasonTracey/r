#pragma once
#include "Position.h"
#include "Terrain.h"

namespace world {
    class MapNode {
        public:
            explicit MapNode(GridPos pos);
            ~MapNode() = default;
            GridPos pos() const {return pos_;}
            Terrain terrain() const {return terrain_;}
            int x() const {return pos_.x;}
            int y() const {return pos_.y;}
            void set_terrain(Terrain terrain);
            void set_height (float h) {height_ = h;}
            float height() const {return height_;}
        private:
            GridPos pos_;
            Terrain terrain_;
            //float feels like the wrong type to me, but resolve later.
            //reasoning is that its quite heavy. I'd choose int but then instinct is to
            //go for a realworld equivalent, and that takes some thinking. metre is too
            //coarse
            float height_; 
    };
}