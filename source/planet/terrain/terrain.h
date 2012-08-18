#ifndef terrain_h
#define terrain_h

#define nullptr NULL

#include <vector>
using std::vector;
#include "terrain_variables.h"
#include "terrain_tile.h"
#include "terrain_corner.h"
#include "terrain_edge.h"

class Planet;
class Tile;
class Corner;
class Edge;
class Vector3;

class Terrain {
public:
	Terrain() {};
	~Terrain() {};

	Terrain_variables var;
	vector<Terrain_tile> tile;
	vector<Terrain_corner> corner;
	vector<Terrain_edge> edge;
};

namespace terrain {
	double area (const Planet*, const Tile*);
	Terrain_corner* corner (Planet*, int);
	Terrain_corner* corner (Planet*, const Corner*);
	double distance (const Planet*, const Tile*, const Tile*);
	Terrain_edge* edge (Planet*, int);
	Terrain_edge* edge (Planet*, const Edge*);
	double elevation (const Planet*, const Vector3&);
	double find_sea_level (Planet*);
	Vector3 from_lat_long (double, double);
	void generate (Planet*);
	void init (Planet*);
	double latitude (const Vector3&);
	double longitude (const Vector3&);
	bool is_coast (const Planet*, const Corner*);
	bool is_water (const Planet*, const Tile*);
	double radius (const Planet*, const Tile*);
	void set_elevation (Planet*);
	void set_sea_level (Planet*);
	Terrain_tile* tile (Planet*, int);
	Terrain_tile* tile (Planet*, const Tile*);
}

#endif
