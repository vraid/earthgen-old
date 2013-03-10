#ifndef corner_h
#define corner_h

#include <array>
#include "../../math/vector3.h"
class Tile;
class Edge;

class Corner {
public:
	Corner (int id);
	
	int id;
	Vector3 v;
	std::array<const Tile*, 3> tiles;
	std::array<const Corner*, 3> corners;
	std::array<const Edge*, 3> edges;
};

int id (const Corner&);
const Vector3& vector (const Corner&);
const std::array<const Tile*, 3>& tiles (const Corner&);
const std::array<const Corner*, 3>& corners (const Corner&);
const std::array<const Edge*, 3>& edges (const Corner&);
const Corner* nth_corner (const Corner&, int);
const Edge* nth_edge (const Corner&, int);

int position (const Corner&, const Tile*);
int position (const Corner&, const Corner*);
int position (const Corner&, const Edge*);

inline int id (const Corner* c) {return id(*c);}
inline const Vector3& vector (const Corner* c) {return vector(*c);}
inline const std::array<const Tile*, 3>& tiles (const Corner* c) {return tiles(*c);}
inline const std::array<const Corner*, 3>& corners (const Corner* c) {return corners(*c);}
inline const std::array<const Edge*, 3>& edges (const Corner* c) {return edges(*c);}
inline const Corner* nth_corner (const Corner* c, int i) {return nth_corner(*c, i);}
inline const Edge* nth_edge (const Corner* c, int i) {return nth_edge(*c, i);}

inline int position (const Corner* c, const Tile* t) {return position(*c, t);}
inline int position (const Corner* c, const Corner* n) {return position(*c, n);}
inline int position (const Corner* c, const Edge* e) {return position(*c, e);}

#endif