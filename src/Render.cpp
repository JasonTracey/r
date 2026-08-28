#include "Render.h"
#include "Map.h"
#include "MapNode.h"
#include "Terrain.h"
#include <array>
#include <cmath>
#include <string_view>
#include <fstream>

namespace world {
    void render(const Map& w, std::ostream& out){
        out << "\nMap:\n";
        for (int y = 0; y < w.height(); y++) {
            for (int x = 0; x < w.width(); x++) {
                out << info(w.node_at({x, y}).terrain()).glyph;
            }
                out << '\n';
        }
    }
    constexpr std::array<std::string_view, 5> height_glyphs = {
        " ",
        "░",
        "▒",
        "▓",
        "█"
    };
    void render_height(const Map& w, std::ostream& out){
        out << "\nMap:\n";
        for (int y = 0; y < w.height(); y++) {
            for (int x = 0; x < w.width(); x++) {
                out << height_glyphs[
                    std::floorf(
                        ((w.node_at({x, y}).height()+1)/2)*5
                    )
                ]; 
            }
                out << '\n';
        }
    }
    void render_height_to_pgm(const Map& w, std::string filename){
        filename.append(".pgm");
        std::ofstream file (filename);
        file << "P2\n"<<w.width()<<' '<<w.height() <<"\n255";
        for (int y = 0; y < w.height(); y++) {
            file << '\n';
            for (int x = 0; x < w.width(); x++) {
                file 
                    << static_cast<int>(std::floorf(
                        ((w.node_at({x, y}).height()+1)/2)*255
                    ))
                    << ' '; 
            }
        }
    }
}