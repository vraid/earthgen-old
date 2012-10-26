#ifndef tile_h
#define tile_h

#include "../../math/vector3.h"
#include "../../math/quaternion.h"
#include <vector>
using std::vector;

class Corner;
class Edge;
class Quaternion;

class Tile {
public:
	Tile();
	~Tile() {};
	
	int id;
	int edges;
	Vector3 v;
	Corner* corner[6];
	Edge* edge[6];
	Tile* tile[6];
};

namespace grid {
	const Corner* corner (const Tile*, int);
	const Edge* edge (const Tile*, int);
	bool point_in_tile (const Tile*, const Vector3&);
	vector<Vector3> polygon (const Tile*);
	vector<Vector3> polygon (const Tile*, const Quaternion&);
	int position (const Tile*, const Corner*);
	int position (const Tile*, const Edge*);
	int position (const Tile*, const Tile*);
	Quaternion reference_rotation (const Tile*);
	const Tile* tile (const Tile*, int);
}

#endif
