#ifndef corner_h
#define corner_h

#include <array>
#include "../../math/vector3.h"

namespace earthgen {

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

inline int id (const Corner& c) {return c.id;}
inline const Vector3& vector (const Corner& c) {return c.v;}
inline const std::array<const Tile*, 3>& tiles (const Corner& c) {return c.tiles;}
inline const std::array<const Corner*, 3>& corners (const Corner& c) {return c.corners;}
inline const std::array<const Edge*, 3>& edges (const Corner& c) {return c.edges;}

const std::array<int,3>& corner_indices ();
const Corner* nth_corner (const Corner&, int);
const Edge* nth_edge (const Corner&, int);

inline int id (const Corner* c) {return id(*c);}
inline const Vector3& vector (const Corner* c) {return vector(*c);}
inline const std::array<const Tile*, 3>& tiles (const Corner* c) {return tiles(*c);}
inline const std::array<const Corner*, 3>& corners (const Corner* c) {return corners(*c);}
inline const std::array<const Edge*, 3>& edges (const Corner* c) {return edges(*c);}
inline const Corner* nth_corner (const Corner* c, int i) {return nth_corner(*c, i);}
inline const Edge* nth_edge (const Corner* c, int i) {return nth_edge(*c, i);}

int position (const Corner&, const Tile*);
int position (const Corner&, const Corner*);
int position (const Corner&, const Edge*);

inline int position (const Corner* c, const Tile* t) {return position(*c, t);}
inline int position (const Corner* c, const Corner* n) {return position(*c, n);}
inline int position (const Corner* c, const Edge* e) {return position(*c, e);}

}

#endif
