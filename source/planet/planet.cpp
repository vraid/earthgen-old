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