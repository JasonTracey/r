#include "Render.h"
#include "WorldMap.h"
#include "WorldMapNode.h"
#include "Terrain.h"

void render(const WorldMap& w, std::ostream& out){
    out << "\nMap:\n";
    for (int y = 0; y < w.height(); y++) {
        for (int x = 0; x < w.width(); x++) {
            out << info(w.node_at({x, y}).terrain()).glyph;
        }
            out << '\n';
    }
}
