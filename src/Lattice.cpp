#include "Lattice.h"
#include "WorldMap.h"
#include <random>
#include <cmath>


namespace {
    int ceil_div(int n, int d) {
        return n/d+(n%d?1:0);
    }
    float unit_lerp(
        float t,
        float a, 
        float b
    ) {
        return (b-a)*t+a;
    }
    float unit_bilerp(
        float tx,
        float ty,
        const std::array<float,4>& q
    ) {
        float r1 = unit_lerp(tx, q[0], q[1]);
        float r2 = unit_lerp(tx, q[2], q[3]);
        return unit_lerp(ty, r1, r2);
    }
    
}

//Public
Lattice::Lattice(WorldMap& world, int spacing, unsigned int seed)
    :
    spacing_(spacing),
    width_(ceil_div(world.width(), spacing)+1),
    height_(ceil_div(world.height(), spacing)+1),
    values_(width_*height_)
{
    // not sure if this should be in construction
    std::mt19937 generator(seed);
    std::uniform_real_distribution<float> distribution(
        -1,
        1
    );
    for (int i=0; i< static_cast<int>(values_.size()); i++) {
        values_[i] = distribution(generator);
    }
}
float Lattice::sample(Coord c) const {
    Frac lcf_subgrid = world_to_lattice_subgrid(c);
    return unit_bilerp(
        lcf_subgrid.x,
        lcf_subgrid.y,
        get_lattice_corners(c)
    );
}


//Private
Lattice::PointF Lattice::world_to_lattice(Coord c) const {
    return {
        static_cast<float>(c.x)/spacing_,
        static_cast<float>(c.y)/spacing_
    };
}
Lattice::Frac Lattice::world_to_lattice_subgrid(Coord c) const {
    float x = static_cast<float>(c.x)/spacing_;
    float y = static_cast<float>(c.y)/spacing_;
    return {
        x-std::floorf(x),
        y-std::floorf(y)
    };

}
std::array<float,4> Lattice::get_lattice_corners(Coord c) const {
    std::array<float,4> corners;
    PointF lcf = world_to_lattice(c);
    Point lc = {
        static_cast<int>(std::floorf(lcf.x)),
        static_cast<int>(std::floorf(lcf.y))
    };
    for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 2; dx++) {
            corners[dx+2*dy] = values_[
                lattice_index({lc.x+dx, lc.y+dy})
            ];
        }   
    }
    return corners;
}