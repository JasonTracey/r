#pragma once
#include <vector>
#include <array>
#include "Coord.h"

// Fwd
class WorldMap;
// Class
class Lattice {
    public:
        Lattice(WorldMap& world, int spacing, unsigned int seed);
        float sample(Coord c) const;
    private:
        struct Point {
            int x, y; //lattice points in lattice space.
        };
        struct PointF {
            float x, y; //lattice points in lattice space.
        };
        struct Frac {
            float x, y; //lattice points in lattice space.
        };

        int spacing_;
        int width_, height_; //lattice points in lattice space.
        std::vector<float> values_;

        PointF world_to_lattice(Coord c) const;
        Frac world_to_lattice_subgrid(Coord c) const;
        std::array<float,4> get_lattice_corners(Coord c) const;
        int lattice_index(Point lc) const {return width_*lc.y+lc.x;}

};