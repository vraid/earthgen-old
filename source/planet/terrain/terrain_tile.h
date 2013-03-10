#ifndef terrain_tile_h
#define terrain_tile_h

#include "terrain_water.h"

class Terrain_tile {
public:
	Terrain_tile () :
		elevation (0), type (type_land) {}

	float elevation;
	Terrain_water water;
	int type;
	enum {type_land = 1, type_water = 2, type_coast = 4};
};

bool is_land (const Terrain_tile&);
bool is_water (const Terrain_tile&);
bool has_coast (const Terrain_tile&);
float elevation (const Terrain_tile&);
float water_depth (const Terrain_tile&);

#endif