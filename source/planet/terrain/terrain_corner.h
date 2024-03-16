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

inline bool is_land (const Terrain_corner& c) {return c.type == c.type_land;}
inline bool is_water (const Terrain_corner& c) {return c.type == c.type_water;}
inline bool is_coast (const Terrain_corner& c) {return c.type == c.type_coast;}

inline float elevation (const Terrain_corner& c) {return c.elevation;}
inline int distance_to_sea (const Terrain_corner& c) {return c.distance_to_sea;}

}

#endif
