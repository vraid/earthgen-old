#ifndef season_h
#define season_h

#include <deque>
#include "climate_tile.h"
#include "climate_edge.h"

namespace earthgen {

class Planet;

class Season {
public:
	Season () {}
	
	std::deque<Climate_tile> tiles;
	std::deque<Climate_edge> edges;
};

const std::deque<Climate_tile>& tiles (const Season&);
const std::deque<Climate_edge>& edges (const Season&);

const Climate_tile& nth_tile (const Season&, int);
const Climate_edge& nth_edge (const Season&, int);

Climate_tile& m_tile (Season&, int);
Climate_edge& m_edge (Season&, int);

}

#endif
