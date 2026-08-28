#pragma once
#include <vector>
#include <array>
#include "Position.h"

// Class
class Lattice {
    public:
        Lattice(int width, int height, int spacing, unsigned int seed);
        float sample(world::GridPos wc) const;
    private:
        struct GridPos {
            int x, y; // Lattice cell by bottom left corner (int part of lattice Position).
        };
        struct FracPos {
            float x, y; // Lattice subcell pos (Fractional part of lattice Position).
        };
        struct Pos {
            GridPos cell;
            FracPos frac;
        };

        int spacing_;
        int width_, height_; //lattice points in lattice space.
        std::vector<float> values_;

        Pos world_to_lattice(world::GridPos c) const;
        std::array<float,4> get_lattice_corners(GridPos lc) const;
        int lattice_index(GridPos lc) const {return width_*lc.y+lc.x;}

};