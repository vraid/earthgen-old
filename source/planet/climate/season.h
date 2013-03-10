#ifndef season_h
#define season_h

#include <deque>
#include "climate_tile.h"
#include "climate_corner.h"
#include "climate_edge.h"
class Planet;

class Season {
public:
	Season () {}
	
	std::deque<Climate_tile> tiles;
	std::deque<Climate_corner> corners;
	std::deque<Climate_edge> edges;
};

const std::deque<Climate_tile>& climate_tiles (const Season&);
const std::deque<Climate_corner>& climate_corners (const Season&);
const std::deque<Climate_edge>& climate_edges (const Season&);

const Climate_tile& nth_climate_tile (const Season&, int);
const Climate_corner& nth_climate_corner (const Season&, int);
const Climate_edge& nth_climate_edge (const Season&, int);

Climate_tile& m_climate_tile (Season&, int);
Climate_corner& m_climate_corner (Season&, int);
Climate_edge& m_climate_edge (Season&, int);

#endif
