#ifndef edge_h
#define edge_h

class Tile;
class Corner;
#include "../../math/vector3.h"

class Edge {
public:
	Edge() {};
	~Edge() {};
	
	int id;
	Vector3 v;
	Tile* tile[2];
	Corner* corner[2];
};

namespace mesh {
	const Corner* corner (const Edge*, int);
	int sign (const Edge*, const Corner*);
	int sign (const Edge*, const Tile*);
	const Tile* tile (const Edge*, int);
}

#endif
