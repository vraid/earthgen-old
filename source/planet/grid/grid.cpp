#include "grid.h"

namespace earthgen {

Grid::Grid () :
	size (0) {}

void Grid::set_size (int size) {
	this->size = size;
	for (int i=0; i<tile_count(size); i++) {
		this->tiles.push_back(Tile(i, i<12 ? 5 : 6));
	}
	for (int i=0; i<corner_count(size); i++) {
		this->corners.push_back(Corner(i));
	}
	for (int i=0; i<edge_count(size); i++) {
		this->edges.push_back(Edge(i));
	}
}

}
