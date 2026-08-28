#include "Lattice.h"
#include <random>
#include <cmath>
#include <tuple>


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
    std::tuple<int, float> decompose_float (float f) {
        float fi = std::floorf(f);
        float ff = f-fi;
        return {static_cast<int>(fi), ff};
    }
    
}

//Public
Lattice::Lattice(int width, int height, int spacing, unsigned int seed)
    :
    spacing_(spacing),
    width_(ceil_div(width, spacing)+1),
    height_(ceil_div(height, spacing)+1),
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
float Lattice::sample(world::GridPos wc) const {
    Pos lp = world_to_lattice(wc);
    return unit_bilerp(
        lp.frac.x,
        lp.frac.y,
        get_lattice_corners(lp.cell)
    );
}


//Private
Lattice::Pos Lattice::world_to_lattice(world::GridPos wc) const {
    Lattice::Pos lpos;
    std::tie(
        lpos.cell.x,
        lpos.frac.x
    ) = decompose_float(static_cast<float>(wc.x)/spacing_);
    std::tie(
        lpos.cell.y,
        lpos.frac.y
    ) = decompose_float(static_cast<float>(wc.y)/spacing_);
    return lpos;
}

std::array<float,4> Lattice::get_lattice_corners(GridPos lc) const {
    std::array<float,4> corners;
    for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 2; dx++) {
            corners[dx+2*dy] = values_[
                lattice_index({lc.x+dx, lc.y+dy})
            ];
        }   
    }
    return corners;
}