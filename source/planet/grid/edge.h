#ifndef edge_h
#define edge_h

#include <array>

namespace earthgen {

class Tile;
class Corner;

class Edge {
public:
	Edge (int id, double ln);
	
	int id;
	double length;
	std::array<const Tile*, 2> tiles;
	std::array<const Corner*, 2> corners;
};

inline int id (const Edge& e) {return e.id;}
inline const std::array<const Tile*, 2>& tiles (const Edge& e) {return e.tiles;}
inline const std::array<const Corner*, 2>& corners (const Edge& e) {return e.corners;}
inline const Tile* nth_tile (const Edge& e, int i) {return e.tiles[i];}
inline const Corner* nth_corner (const Edge& e, int i) {return e.corners[i];}

inline int id (const Edge* e) {return id(*e);}
inline const std::array<const Tile*, 2>& tiles (const Edge* e) {return tiles(*e);}
inline const std::array<const Corner*, 2>& corners (const Edge* e) {return corners(*e);}
inline const Tile* nth_tile (const Edge* e, int n) {return nth_tile(*e, n);}
inline const Corner* nth_corner (const Edge* e, int n) {return nth_corner(*e, n);}

const std::array<int,2>& edge_indices ();

int position (const Edge&, const Tile*);
int position (const Edge&, const Corner*);
int sign (const Edge&, const Tile*);
int sign (const Edge&, const Corner*);

inline int position (const Edge* e, const Tile* t) {return position(*e, t);}
inline int position (const Edge* e, const Corner* c) {return position(*e, c);}
inline int sign (const Edge* e, const Tile* t) {return sign(*e, t);}
inline int sign (const Edge* e, const Corner* c) {return sign(*e, c);}

}

#endif
