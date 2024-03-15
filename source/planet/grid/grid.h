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

inline const std::vector<Tile>& tiles (const Grid& grid) {return grid.tiles;}
inline const std::vector<Corner>& corners (const Grid& grid) {return grid.corners;}
inline const std::vector<Edge>& edges (const Grid& grid) {return grid.edges;}

inline const Tile* nth_tile (const Grid& grid, int n) {return &grid.tiles[n];}
inline const Corner* nth_corner (const Grid& grid, int n) {return &grid.corners[n];}
inline const Edge* nth_edge (const Grid& grid, int n) {return &grid.edges[n];}

inline int tile_count (const Grid& grid) {return grid.tiles.size();}
inline int corner_count (const Grid& grid) {return grid.corners.size();}
inline int edge_count (const Grid& grid) {return grid.edges.size();}

}

#endif
