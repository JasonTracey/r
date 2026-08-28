#pragma once
#include <cstdint>
#include <string_view>
#include "Colour.h"
#include <cmath>

enum class Terrain : uint8_t {
    Grass,
    ShallowWater,
    Soil,
    Count
};

struct TerrainInfo {
    Terrain id;
    std::string_view name;
    Colour colour;
    char glyph;
};

const TerrainInfo& info(Terrain t);
Terrain terrain_from_value(float value); 