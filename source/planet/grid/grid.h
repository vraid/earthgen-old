#ifndef grid_h
#define grid_h

#include "tile.h"
#include "corner.h"
#include "edge.h"
#include "create_grid.h"

namespace earthgen {

class Grid {
public:
	void set_size(int);
	int size;
	std::vector<Tile> tiles;
	std::vector<Corner> corners;
	std::vector<Edge> edges;
};

int tile_count (int size);
int corner_count (int size);
int edge_count (int size);

}

#endif
