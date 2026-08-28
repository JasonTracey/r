# TODO

Ordered by dependency — each item unblocks the ones under it.

## Done

- [x] `WorldMapNode::set_terrain(Terrain)` — the write path into a tile.
- [x] `WorldMap::width()` / `height()` accessors.
- [x] `render(const WorldMap&, std::ostream&)` — glyphs, row by row.
- [x] `generate(WorldMap&, unsigned seed)` — white noise. Proved the pipeline.
- [x] Value noise: `Lattice` (coarse grid + bilinear sampling), `generate_value`.
      Verified: same seed gives the same map; spacing=1 degenerates to white noise.

---

## 1. Lattice tidy-up (small, do first)

- [x] `#include <array>` in `Lattice.h` — it declares `std::array` but only gets it
      by accident, via `<vector>`.
- [x] `WorldMap.h` -> forward declaration `class WorldMap;` in the header.
      Only `WorldMap&` is used, so the full definition isn't needed.
- [x] Delete dead code: `UnitCornerValues` struct, `#include <iostream>`,
      `#include "Terrain.h"`, stray `;` at the top of the constructor body.
- [ ] Fold `world_to_lattice` + `world_to_lattice_subgrid` into one `locate()`
      returning cell + fraction. `get_lattice_corners` then takes the cell.
      Reason: world->lattice mapping is currently defined in two places that must
      agree. One definition, and `PointF` disappears.

## 2. Height map as a first-class thing

Right now noise maps straight to terrain. Split those: generate a height field,
then decide terrain from it (plus whatever else) as a separate step.

- [ ] **Decide where height lives.** Two options, and this blocks everything below:
      - a `float height_` on `WorldMapNode` — simple, costs 4 bytes/tile, and the
        river walk can read it through `node_at`
      - a separate float grid alongside the map — keeps nodes lean, but now two
        structures must stay in step
- [ ] Generate the height field from the existing `Lattice` sampling.
- [ ] Render height directly as ASCII shading (e.g. ` .:-=+*#%@`) so the field is
      visible on its own, before terrain is involved. Same reasoning as building
      the renderer before the generator.

## 3. Rivers

- [ ] **Neighbour queries on `WorldMap`** — the downhill walk needs "what's next to
      this tile, and is it on the map". Doesn't exist yet; `coord_inbounds` is the
      building block. 4-way or 8-way is a real choice: 8-way gives more natural
      diagonals, 4-way is simpler and rivers look blockier.
- [ ] Pick a source: somewhere on the highest edge.
- [ ] Walk downhill to the lowest neighbour, marking water, until reaching an edge
      or the sea.
- [ ] Handle the walk getting stuck in a local minimum (a pit with no lower
      neighbour). Options: stop, form a lake, or fill the pit and continue.
      This WILL happen with noise-generated terrain — worth deciding up front.

## 4. Terrain from height (+ whatever else)

- [ ] Replace the direct noise->terrain mapping with something driven by height,
      distance to water, and possibly a second noise field (moisture).
      Deliberately vague: decide once heights and rivers are visible.

## 5. Better noise — deferred

Value noise is sufficient until the above is working. Not worth the effort yet.

- [ ] Smoothstep on the interpolation weight (`t*t*(3-2*t)`) — one line, removes
      the visible creases along lattice lines. Cheapest possible improvement.
- [ ] Multiple octaves (fBm): sum several lattices at doubling frequency and
      halving amplitude. This is what makes terrain look like terrain.
- [ ] Perlin noise (gradients at lattice points instead of values).
- [ ] Simplex noise — mainly a win in 3D+; probably never needed here.

## Housekeeping (whenever)

- [ ] Retire `src/game.cpp` (legacy demo) once nothing references it.
- [ ] Drop `WorldMap::nodes()` — `node_at()` supersedes it, and it leaks the
      storage layout that `index()` exists to hide.
- [ ] Legacy classes (`Location`, `Resource`, `Species`, `Unit`, `Stockpile`)
      are reference-only; delete when no longer useful.

## Parked

- `TerrainInfo::colour` is unused until there's a real renderer.
- Save/load will need stable terrain IDs — see the note about explicit enum values.
- The -0.5 lattice offset. Try smoothstep first; it may be the whole problem.
