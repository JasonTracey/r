# TODO

Ordered by dependency — each item unblocks the ones under it.

## 1. Finish the mutation path
- [x] `WorldMapNode::set_terrain(Terrain)` — the non-const `node_at` exists, but the
      node still has no setter, so nothing can actually write terrain.

## 2. Expose map dimensions
- [x] `WorldMap::width()` / `height()` accessors.
      The renderer and generator both need to loop over the grid, and neither can
      without these. Trivial const getters in the header.

## 3. Renderer  (do this BEFORE generation)
- [x] `render(const WorldMap&)` in its own file, printing `info(node.terrain()).glyph`
      row by row to stdout.
- [x] Add `src/Render.cpp` to `SRC` in the Makefile.
      Rationale: generation written blind is guesswork. Once the map is visible,
      every later change verifies itself by eye.

## 4. Generation — step 1: random
- [x] `generate(WorldMap&, unsigned seed)` in its own file, terrain picked per tile.
- [x] Use `<random>` (`std::mt19937` + `std::uniform_int_distribution`), not `rand()`.
- [x] Add `src/WorldGen.cpp` to `SRC`.
      This will look like TV static. That's fine — its job is proving the
      write path and renderer work end to end.

## 5. Generation — step 2: coherent noise
- [ ] Value noise or Perlin/simplex over the grid.
- [ ] Threshold the noise field into terrain bands (low -> water, mid -> grass, high -> soil).
      Static looks wrong because real terrain is spatially correlated; noise is what
      makes neighbours resemble each other.

## Housekeeping (whenever)
- [ ] Retire `src/game.cpp` (legacy demo) once nothing references it.
- [ ] Drop `WorldMap::nodes()` — `node_at()` supersedes it, and it leaks the
      storage layout that `index()` exists to hide.
- [ ] Legacy classes (`Location`, `Resource`, `Species`, `Unit`, `Stockpile`)
      are reference-only; delete when no longer useful.

## Parked
- `TerrainInfo::colour` is unused until there's a real renderer.
- Save/load will need stable terrain IDs — see the note about explicit enum values.
