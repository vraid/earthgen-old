#ifndef terrain_tile_h
#define terrain_tile_h

namespace earthgen {

class Terrain_water {
public:
	Terrain_water () :
		surface (0), depth (0) {}

	float surface;
	float depth;
};

class Terrain_tile {
public:
	Terrain_tile () :
		elevation (0), type (type_land) {}

	float elevation;
	Terrain_water water;
	int type;
	enum {type_land = 1, type_water = 2, type_coast = 4};
};

inline bool is_land (const Terrain_tile& t) {return t.type & t.type_land;}
inline bool is_water (const Terrain_tile& t) {return t.type & t.type_water;}
inline bool has_coast (const Terrain_tile& t) {return t.type & t.type_coast;}

inline float elevation (const Terrain_tile& t) {return t.elevation;}
inline float water_depth (const Terrain_tile& t) {return t.water.depth;}

}

#endif
