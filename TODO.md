# TODO

Ordered by dependency — each item unblocks the ones under it.

## Done

- [x] `MapNode::set_terrain(Terrain)` — the write path into a tile.
- [x] `Map::width()` / `height()` accessors.
- [x] `render(const Map&, std::ostream&)` — glyphs, row by row.
- [x] `generate(Map&, unsigned seed)` — white noise. Proved the pipeline.
- [x] Value noise: `Lattice` (coarse grid + bilinear sampling), `generate_value`.
      Verified: same seed gives the same map; spacing=1 degenerates to white noise.

---

## 1. Lattice tidy-up (small, do first)

- [x] `#include <array>` in `Lattice.h` — it declares `std::array` but only gets it
      by accident, via `<vector>`.
- [x] `Map.h` -> forward declaration `class Map;` in the header.
      Only `Map&` is used, so the full definition isn't needed.
- [x] Delete dead code: `UnitCornerValues` struct, `#include <iostream>`,
      `#include "Terrain.h"`, stray `;` at the top of the constructor body.
- [x] Fold `world_to_lattice` + `world_to_lattice_subgrid` into one `locate()`
      returning cell + fraction. `get_lattice_corners` then takes the cell.
      Reason: world->lattice mapping is currently defined in two places that must
      agree. One definition, and `PointF` disappears.

## 2. Height map as a first-class thing

Right now noise maps straight to terrain. Split those: generate a height field,
then decide terrain from it (plus whatever else) as a separate step.

- [x] **Decide where height lives.** `float height_` on `MapNode`.
- [x] Generate the height field from the existing `Lattice` sampling.
- [x] `render_height` — ASCII shading, visible before terrain is involved.

### 2a. Fix the banding and init  <- NEXT

- [ ] Clamp the band index in `render_height`, and derive the band count from
      `height_glyphs.size()` instead of the hardcoded `5`:
          int i = std::clamp(static_cast<int>((h+1)/2*N), 0, N-1);
      `<algorithm>`, C++17. At h == 1.0 the current expression indexes one past
      the end. Safe today only because uniform_real_distribution is half-open —
      fBm will break that assumption, so fix it before adding octaves.
- [ ] Clamp the input too: `std::clamp(h, -1.0f, 1.0f)`. Summed octaves exceed
      +/-1 unless normalised.
- [ ] Swap the Unicode blocks for an ASCII ramp (" .:-=+*#%@"). The shade
      characters are missing from many monospace fonts, so editors substitute a
      fallback with different metrics - hence the uneven heights.
      (Terrain keeps its char glyphs; this is only the height renderer.)
- [ ] **`MapNode::height_` is never initialised.** Add `height_(0.0f)` to the
      constructor's initialiser list. Confirmed: reading an ungenerated map gives
      garbage (5.04467e-43 on the first node, zeros after - i.e. luck, not zeroing).
      -Wall does NOT catch uninitialised members, only locals.

### 2b. Image output  [done]

- [x] `render_height_to_pgm(const Map&, std::string filename)` writing netpbm P2.
      Verified: header well-formed, value count matches width*height, values in
      0-255 with a real spread.
      Note it opens its own ofstream rather than taking `std::ostream&` like the
      other two renderers - deliberate, since it appends the .pgm extension.
- [ ] Add the input clamp here too (see 2a). Currently unclamped; safe only
      because heights happen to land inside [-1,1].

## 3. Rivers

- [ ] **Neighbour queries on `Map`** — the downhill walk needs "what's next to
      this tile, and is it on the map". Doesn't exist yet; `Position_inbounds` is the
      building block. 4-way or 8-way is a real choice: 8-way gives more natural
      diagonals, 4-way is simpler and rivers look blockier.
- [ ] Pick a source: somewhere on the highest edge.
- [ ] Walk downhill to the lowest neighbour, marking water, until reaching an edge
      or the sea.
- [ ] Handle the walk getting stuck in a local minimum (a pit with no lower
      neighbour). Options: stop, form a lake, or fill the pit and continue.
      This WILL happen with noise-generated terrain — worth deciding up front.

## 4. Stay on heightmaps for a while

Deliberate. Terrain types stay as they are (everything Soil) until rivers exist.
No sea level, no height banding.

Reason: large bodies of water are big impassable blocks - they eat map area and
give nothing back. Rivers occupy very little space while introducing a natural
barrier and a point of focus. Same logic applies to mountains, cliffs and any
other impassable terrain: sparse and interesting beats large and blocking.

Candidates, roughly in order of payoff:

- [ ] Smoothstep + octaves (section 6) - the height field itself getting better.
- [ ] Rivers (section 3).
- [ ] Lakes, from the pit-filling that rivers force you to handle anyway.
      Small ones. Same argument as above.
- [ ] Erosion - carve the height field along river paths. Expensive, but this is
      what makes generated terrain stop looking like noise.

## 5. Terrain, properly (much later)

- [ ] Needs a second field to derive from: moisture, or distance-to-water once
      rivers exist. Grass vs soil is a vegetation question, not a height one.
- [ ] Deliberately unspecified. Decide when there is real data to decide from.
- [ ] `terrain_from_value` (even-division height -> terrain) gets deleted at that
      point. It invents a relationship between height and terrain that isn't real.

## 6. Better noise — deferred

Value noise is sufficient until the above is working. Not worth the effort yet.

- [ ] Smoothstep on the interpolation weight (`t*t*(3-2*t)`) — one line, removes
      the visible creases along lattice lines. Cheapest possible improvement.
- [ ] Multiple octaves (fBm): sum several lattices at doubling frequency and
      halving amplitude. This is what makes terrain look like terrain.
- [ ] Perlin noise (gradients at lattice points instead of values).
- [ ] Simplex noise — mainly a win in 3D+; probably never needed here.

## Housekeeping (whenever)

- [ ] Retire `src/game.cpp` (legacy demo) once nothing references it.
- [ ] Drop `Map::nodes()` — `node_at()` supersedes it, and it leaks the
      storage layout that `index()` exists to hide.
- [ ] Legacy classes (`Location`, `Resource`, `Species`, `Unit`, `Stockpile`)
      are reference-only; delete when no longer useful.

## Resolved

- `float height_` is the right type. 4 bytes/tile is 4 MB at a million tiles.
  Height is currently a relative ordering (is this neighbour lower?), not a
  measurement - comparison needs ordering, not units. Picking a real-world unit
  now means choosing a scale before knowing what it is for, and quantising away
  resolution the interpolation gives free. If physical arithmetic ever needs it
  (water volume, fall damage), fixed-point int16 in decimetres is the usual
  answer. Delete the "float feels wrong" comment in MapNode.h.

## Parked

- `TerrainInfo::colour` is unused until there's a real renderer.
- Save/load will need stable terrain IDs — see the note about explicit enum values.
- The -0.5 lattice offset. Try smoothstep first; it may be the whole problem.
