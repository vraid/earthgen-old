#ifndef planet_h
#define planet_h

#include "grid/grid.h"
#include "terrain/terrain.h"
#include "climate/climate.h"

class Planet {
public:
	Planet ();
	~Planet ();
	
	Grid grid;
	Terrain* terrain;
	Climate* climate;
};

void clear (Planet&);
void set_grid_size (Planet&, int);

const std::deque<Tile>& tiles (const Planet&);
const std::deque<Corner>& corners (const Planet&);
const std::deque<Edge>& edges (const Planet&);

const Tile* nth_tile (const Planet&, int);
const Corner* nth_corner (const Planet&, int);
const Edge* nth_edge (const Planet&, int);

int tile_count (const Planet&);
int corner_count (const Planet&);
int edge_count (const Planet&);

#endif
