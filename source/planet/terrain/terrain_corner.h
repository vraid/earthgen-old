#ifndef terrain_corner_h
#define terrain_corner_h

namespace earthgen {

class Terrain_corner {
public:
	Terrain_corner () :
		elevation (0), distance_to_sea(-1), type(type_land) {}

	float elevation;
	int distance_to_sea;
	int type;
	enum {type_land = 1, type_water = 2, type_coast = 4};
};

bool is_land (const Terrain_corner&);
bool is_water (const Terrain_corner&);
bool is_coast (const Terrain_corner&);
float elevation (const Terrain_corner&);
int distance_to_sea (const Terrain_corner&);

}

#endif
