#ifndef terrain_tile_h
#define terrain_tile_h

namespace earthgen {

class Terrain_water {
public:
	Terrain_water () :
		surface (0), depth (0) {}

	double surface;
	double depth;
};

class Terrain_tile {
public:
	Terrain_tile () :
		elevation (0), type (type_land) {}

	double elevation;
	Terrain_water water;
	int type;
	enum {type_land = 1, type_water = 2, type_coast = 4};
};

class Terrain_corner {
public:
	Terrain_corner () :
		elevation (0), distance_to_sea(-1), type(type_land) {}

	double elevation;
	int distance_to_sea;
	int type;
	enum {type_land = 1, type_water = 2, type_coast = 4};
};

class Terrain_edge {
public:
	Terrain_edge () :
		type (type_land) {}

	int type;
	enum {type_land = 1, type_water = 2, type_coast = 4};
};

inline bool is_land (const Terrain_tile& t) {return t.type & t.type_land;}
inline bool is_water (const Terrain_tile& t) {return t.type & t.type_water;}
inline bool has_coast (const Terrain_tile& t) {return t.type & t.type_coast;}

inline double elevation (const Terrain_tile& t) {return t.elevation;}
inline double water_depth (const Terrain_tile& t) {return t.water.depth;}

inline bool is_land (const Terrain_corner& c) {return c.type == c.type_land;}
inline bool is_water (const Terrain_corner& c) {return c.type == c.type_water;}
inline bool is_coast (const Terrain_corner& c) {return c.type == c.type_coast;}

inline double elevation (const Terrain_corner& c) {return c.elevation;}
inline int distance_to_sea (const Terrain_corner& c) {return c.distance_to_sea;}

inline bool is_land (const Terrain_edge& e) {return e.type == e.type_land;}
inline bool is_water (const Terrain_edge& e) {return e.type == e.type_water;}
inline bool is_coast (const Terrain_edge& e) {return e.type == e.type_coast;}

}

#endif
