#ifndef terrain_edge_h
#define terrain_edge_h

class Terrain_edge {
public:
	Terrain_edge () :
		type (type_land) {}

	int type;
	enum {type_land = 1, type_water = 2, type_coast = 4};
};

bool is_land (const Terrain_edge&);
bool is_water (const Terrain_edge&);
bool is_coast (const Terrain_edge&);

#endif