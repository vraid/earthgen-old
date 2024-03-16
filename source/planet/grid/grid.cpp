#include "grid.h"

namespace earthgen {

Grid::Grid () :
	size (0) {}

void Grid::set_size (int n) {
	size = n;
	tiles.clear();
	corners.clear();
	edges.clear();
	for (int i=0; i<tile_count(n); i++) {
		tiles.push_back(Tile(i, i<12 ? 5 : 6));
	}
	corners.reserve(corner_count(n));
	edges.reserve(edge_count(n));
}

}
