#ifndef tile_h
#define tile_h

#include <vector>
#include "../../math/vector2.h"
#include "../../math/vector3.h"
#include "../../math/quaternion.h"
class Corner;
class Edge;

class Tile {
public:
	Tile (int id, int edge_count);
	
	int id;
	int edge_count;
	Vector3 v;
	std::vector<const Tile*> tiles;
	std::vector<const Corner*> corners;
	std::vector<const Edge*> edges;
};

int id (const Tile&);
int edge_count (const Tile&);
const Vector3& vector (const Tile&);
const std::vector<const Tile*>& tiles (const Tile&);
const std::vector<const Corner*>& corners (const Tile&);
const std::vector<const Edge*>& edges (const Tile&);
const Tile* nth_tile (const Tile&, int);
const Corner* nth_corner (const Tile&, int);
const Edge* nth_edge (const Tile&, int);

int position (const Tile&, const Tile*);
int position (const Tile&, const Corner*);
int position (const Tile&, const Edge*);

Quaternion reference_rotation (const Tile*, Quaternion);
std::vector<Vector2> polygon (const Tile*, Quaternion);

inline int id (const Tile* t) {return id(*t);}
inline int edge_count (const Tile* t) {return edge_count(*t);}
inline const Vector3& vector (const Tile* t) {return vector(*t);}
inline const std::vector<const Tile*>& tiles (const Tile* t) {return tiles(*t);}
inline const std::vector<const Corner*>& corners (const Tile* t) {return corners(*t);}
inline const std::vector<const Edge*>& edges (const Tile* t) {return edges(*t);}
inline const Tile* nth_tile (const Tile* t, int n) {return nth_tile(*t, n);}
inline const Corner* nth_corner (const Tile* t, int n) {return nth_corner(*t, n);}
inline const Edge* nth_edge (const Tile* t, int n) {return nth_edge(*t, n);}

inline int position (const Tile* t, const Tile* n) {return position(*t, n);}
inline int position (const Tile* t, const Corner* c) {return position(*t, c);}
inline int position (const Tile* t, const Edge* e) {return position(*t, e);}

#endif