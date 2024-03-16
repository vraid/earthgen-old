#ifndef season_h
#define season_h

#include <vector>
#include "climate_structs.h"

namespace earthgen {

class Planet;

class Season {
public:
	Season () {}
	
	std::vector<Climate_tile> tiles;
	std::vector<Climate_edge> edges;
};

inline const std::vector<Climate_tile>& tiles (const Season& s) {return s.tiles;}
inline const std::vector<Climate_edge>& edges (const Season& s) {return s.edges;}

inline const Climate_tile& nth_tile (const Season& s, int n) {return s.tiles[n];}
inline const Climate_edge& nth_edge (const Season& s, int n) {return s.edges[n];}

inline Climate_tile& m_tile (Season& s, int n) {return s.tiles[n];}
inline Climate_edge& m_edge (Season& s, int n) {return s.edges[n];}

}

#endif
