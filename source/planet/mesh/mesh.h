#ifndef mesh_h
#define mesh_h

#include <vector>
using std::vector;

#include "tile.h"
#include "corner.h"
#include "edge.h"
#include "create_mesh.h"

class Planet;

class Mesh {
public:
	Mesh() {};
	~Mesh() {};

	int size;
	int tiles;
	int corners;
	int edges;
	
	std::vector<Tile> tile;
	std::vector<Corner> corner;
	std::vector<Edge> edge;
};

namespace mesh {
	const Corner* corner (const Planet*, int);
	int corners (const Planet*);
	const Edge* edge (const Planet*, int);
	int edges (const Planet*);
	void init (Mesh*, int);
	void rotate (Mesh*, const Quaternion&);
	const Tile* select_tile (const Planet*, const Vector3&);
	const Tile* tile (const Planet*, int);
	int tiles (const Planet*);
}

#endif
