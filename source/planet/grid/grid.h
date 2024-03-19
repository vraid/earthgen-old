#ifndef grid_h
#define grid_h

#include "tile.h"
#include "corner.h"
#include "edge.h"
#include <cmath>

namespace earthgen {

class Grid {
public:
	Grid ();

	void set_size(int);
	int size;
	std::vector<Tile> tiles;
	std::vector<Corner> corners;
	std::vector<Edge> edges;
};

inline const std::vector<Tile>& tiles (const Grid& grid) {return grid.tiles;}
inline const std::vector<Corner>& corners (const Grid& grid) {return grid.corners;}
inline const std::vector<Edge>& edges (const Grid& grid) {return grid.edges;}

inline const Tile* nth_tile (const Grid& grid, int n) {return &grid.tiles[n];}
inline const Corner* nth_corner (const Grid& grid, int n) {return &grid.corners[n];}
inline const Edge* nth_edge (const Grid& grid, int n) {return &grid.edges[n];}

inline int tile_count (int size) {return 2+10*std::pow(3,size);}
inline int corner_count (int size) {return 20*std::pow(3,size);}
inline int edge_count (int size) {return 30*std::pow(3,size);}

inline int tile_count (const Grid& grid) {return grid.tiles.size();}
inline int corner_count (const Grid& grid) {return grid.corners.size();}
inline int edge_count (const Grid& grid) {return grid.edges.size();}

}

#endif
