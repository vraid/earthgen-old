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

inline const std::deque<Climate_tile>& tiles (const Season& s) {return s.tiles;}
inline const std::deque<Climate_edge>& edges (const Season& s) {return s.edges;}

inline const Climate_tile& nth_tile (const Season& s, int n) {return s.tiles[n];}
inline const Climate_edge& nth_edge (const Season& s, int n) {return s.edges[n];}

inline Climate_tile& m_tile (Season& s, int n) {return s.tiles[n];}
inline Climate_edge& m_edge (Season& s, int n) {return s.edges[n];}

}

#endif
