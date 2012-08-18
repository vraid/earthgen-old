#ifndef terrain_tile_h
#define terrain_tile_h

#include "terrain_water.h"

class Terrain_tile {
public:
	Terrain_tile() {
		elevation = 0;
	}
	~Terrain_tile() {};

	double elevation;
	Terrain_water water;

	bool is_land;
	bool is_water;
	bool has_coast;
};

#endif
