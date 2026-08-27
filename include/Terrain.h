#pragma once
#include <cstdint>
#include <string_view>
#include "Colour.h"

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