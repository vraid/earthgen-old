#include "planet.h"
#include "grid/grid.h"

Planet::Planet () {
	grid = size_n_grid(0);
	terrain = new Terrain();
	climate = new Climate();
}

Planet::~Planet () {
	delete grid;
	delete terrain;
	delete climate;
}

void clear (Planet& p) {
	set_grid_size(p, 0);
	clear_terrain(p);
	clear_climate(p);
}

void set_grid_size (Planet& p, int size) {
	delete p.grid;
	p.grid = size_n_grid(size);
}

const std::deque<Tile>& tiles (const Planet& p) {return p.grid->tiles;}
const std::deque<Corner>& corners (const Planet& p) {return p.grid->corners;}
const std::deque<Edge>& edges (const Planet& p) {return p.grid->edges;}

const Tile* nth_tile (const Planet& p, int n) {return &p.grid->tiles[n];}
const Corner* nth_corner (const Planet& p, int n) {return &p.grid->corners[n];}
const Edge* nth_edge (const Planet& p, int n) {return &p.grid->edges[n];}

int tile_count (const Planet& p) {return p.grid->tiles.size();}
int corner_count (const Planet& p) {return p.grid->corners.size();}
int edge_count (const Planet& p) {return p.grid->edges.size();}
