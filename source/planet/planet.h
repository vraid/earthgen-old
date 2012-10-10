#ifndef planet_h
#define planet_h

#define nullptr NULL

#include <vector>
#include <map>
using std::vector;
using std::map;

#include "../math/math.h"
#include "parameters.h"
#include "grid/grid.h"
#include "terrain/terrain.h"
#include "climate/climate.h"

class Planet {
public:
	Planet() {
		grid = nullptr;
		terrain = new Terrain();
		climate = new Climate();
	}
	~Planet() {
		delete grid;
		delete terrain;
		delete climate;
	}

	Parameters par;
	Grid* grid;
	Terrain* terrain;
	Climate* climate;
};

#endif
