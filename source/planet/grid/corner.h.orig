#ifndef corner_h
#define corner_h

class Tile;
class Edge;
#include "../../math/vector3.h"

class Corner {
public:
	Corner() {};
	~Corner() {};
	
	int id;
	Vector3 v;
	Tile* tile[3];
	Corner* corner[3];
	Edge* edge[3];
};

namespace grid {
	const Corner* corner (const Corner*, int);
	const Edge* edge (const Corner*, int);
	int position (const Corner*, const Corner*);
	int position (const Corner*, const Edge*);
	int position (const Corner*, const Tile*);
	const Tile* tile (const Corner*, int);
}

#endif
