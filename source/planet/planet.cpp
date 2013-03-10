#include "planet.h"
#include "grid/grid.h"

Planet::Planet () {
	grid = size_n_grid(0);
}

Planet::~Planet () {
	delete grid;
}

void clear (Planet& p) {
	set_grid_size(p, 0);
	clear_terrain(p);
	clear_climate(p);
}