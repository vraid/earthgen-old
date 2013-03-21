#include "season.h"
#include "../planet.h"

const std::deque<Climate_tile>& tiles (const Season& s) {return s.tiles;}
const std::deque<Climate_corner>& corners (const Season& s) {return s.corners;}
const std::deque<Climate_edge>& edges (const Season& s) {return s.edges;}

const Climate_tile& nth_tile (const Season& s, int n) {return s.tiles[n];}
const Climate_corner& nth_corner (const Season& s, int n) {return s.corners[n];}
const Climate_edge& nth_edge (const Season& s, int n) {return s.edges[n];}

Climate_tile& m_tile (Season& s, int n) {return s.tiles[n];}
Climate_corner& m_corner (Season& s, int n) {return s.corners[n];}
Climate_edge& m_edge (Season& s, int n) {return s.edges[n];}