#ifndef tile_h
#define tile_h

#include <vector>
#include "../../math/vector3.h"

namespace earthgen {

class Corner;
class Edge;

class Tile {
public:
	Tile (int id, int edge_count);
	
	int id;
	int edge_count;
	Vector3 v;
	double area;
	std::vector<const Tile*> tiles;
	std::vector<const Corner*> corners;
	std::vector<const Edge*> edges;
};

inline int id (const Tile& t) {return t.id;}
inline int edge_count (const Tile& t) {return t.edge_count;}
inline const Vector3& vector (const Tile& t) {return t.v;}
inline double area (const Tile& t) {return t.area;}
inline const std::vector<const Tile*>& tiles (const Tile& t) {return t.tiles;}
inline const std::vector<const Corner*>& corners (const Tile& t) {return t.corners;}
inline const std::vector<const Edge*>& edges (const Tile& t) {return t.edges;}

inline int id (const Tile* t) {return id(*t);}
inline int edge_count (const Tile* t) {return edge_count(*t);}
inline const Vector3& vector (const Tile* t) {return vector(*t);}
inline double area (const Tile* t) {return area(*t);}
inline const std::vector<const Tile*>& tiles (const Tile* t) {return tiles(*t);}
inline const std::vector<const Corner*>& corners (const Tile* t) {return corners(*t);}
inline const std::vector<const Edge*>& edges (const Tile* t) {return edges(*t);}

const std::vector<int>& indices (const Tile&);
const Tile* nth_tile (const Tile&, int);
const Corner* nth_corner (const Tile&, int);
const Edge* nth_edge (const Tile&, int);
int position (const Tile&, const Tile*);
int position (const Tile&, const Corner*);
int position (const Tile&, const Edge*);

inline const std::vector<int>& indices(const Tile* t) {return indices(*t);}
inline const Tile* nth_tile (const Tile* t, int n) {return nth_tile(*t, n);}
inline const Corner* nth_corner (const Tile* t, int n) {return nth_corner(*t, n);}
inline const Edge* nth_edge (const Tile* t, int n) {return nth_edge(*t, n);}
inline int position (const Tile* t, const Tile* n) {return position(*t, n);}
inline int position (const Tile* t, const Corner* c) {return position(*t, c);}
inline int position (const Tile* t, const Edge* e) {return position(*t, e);}

}

#endif
