#ifndef edge_h
#define edge_h

#include <array>
class Tile;
class Corner;

class Edge {
public:
	Edge (int id);
	
	int id;
	std::array<const Tile*, 2> tiles;
	std::array<const Corner*, 2> corners;
};

int id (const Edge&);
const std::array<const Tile*, 2>& tiles (const Edge&);
const std::array<const Corner*, 2>& corners (const Edge&);
const Tile* nth_tile (const Edge&, int);
const Corner* nth_corner (const Edge&, int);

int position (const Edge&, const Tile*);
int position (const Edge&, const Corner*);
int sign (const Edge&, const Tile*);
int sign (const Edge&, const Corner*);

inline int id (const Edge* e) {return id(*e);}
inline const std::array<const Tile*, 2>& tiles (const Edge* e) {return tiles(*e);}
inline const std::array<const Corner*, 2>& corners (const Edge* e) {return corners(*e);}
inline const Tile* nth_tile (const Edge* e, int n) {return nth_tile(*e, n);}
inline const Corner* nth_corner (const Edge* e, int n) {return nth_corner(*e, n);}

inline int position (const Edge* e, const Tile* t) {return position(*e, t);}
inline int position (const Edge* e, const Corner* c) {return position(*e, c);}
inline int sign (const Edge* e, const Tile* t) {return sign(*e, t);}
inline int sign (const Edge* e, const Corner* c) {return sign(*e, c);}

#endif
