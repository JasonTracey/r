#include "Terrain.h"
#include <array>
#include <stdexcept>
constexpr int terrain_table_size = static_cast<int>(Terrain::Count);
constexpr std::array<TerrainInfo, terrain_table_size> terrain_table = {{
    {Terrain::Grass, "Grass", {107u, 142u, 35u, 255u}, ','},
    {Terrain::ShallowWater, "Shallow Water", {135u,206u, 250u, 255u}, '~'},
    {Terrain::Soil, "Soil", {139u, 69u, 19u, 255u}, '#'}
}};
constexpr bool is_terrain_ordered() {
    for (int i=0; i<terrain_table_size; i++) {
        if (terrain_table[i].id != static_cast<Terrain>(i)) {
            return false;
        }
    }
    return true;
}
static_assert(
    is_terrain_ordered(),
    "terrain_table must match Terrain enum order and size"
);
const TerrainInfo& info(Terrain t) {
    if (static_cast<int>(t)>=terrain_table_size)
    {
        throw std::out_of_range("Terrain not found!");
    }
    
    return terrain_table[static_cast<uint8_t>(t)];
}
Terrain terrain_from_value(float value) {
    int terrain_i = std::truncf(((value+1)/2) * static_cast<float>(Terrain::Count));
    if (static_cast<Terrain>(terrain_i) == Terrain::Count) {
        return static_cast<Terrain>(terrain_i-1);
    }
    return static_cast<Terrain>(terrain_i);} //this feels suuuuper messy REFACTOR?