#ifndef planet_h
#define planet_h

#define nullptr NULL

#include <vector>
#include <map>
using std::vector;
using std::map;

#include "../math/math.h"
#include "parameters.h"
#include "mesh/mesh.h"
#include "terrain/terrain.h"
#include "climate/climate.h"

class Planet {
public:
	Planet() {};
	~Planet() {};

	Parameters par;
	Mesh* mesh;
	Terrain* terrain;
	Climate* climate;
};

#endif
