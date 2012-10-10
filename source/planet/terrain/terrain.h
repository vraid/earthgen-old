#ifndef terrain_h
#define terrain_h

#define nullptr NULL

#include <vector>
#include "terrain_variables.h"
#include "terrain_tile.h"
#include "terrain_corner.h"
#include "terrain_edge.h"
#include "water_body.h"

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
	std::vector<Terrain_tile> tile;
	std::vector<Terrain_corner> corner;
	std::vector<Terrain_edge> edge;

	std::vector<Water_body> water_bodies;
};

namespace terrain {
	void generate (Planet*);
	void init (Planet*);
	void set_elevation (Planet*);
	void smoothe_elevation (Planet*);
	void scale_elevation (Planet*);
	void set_sea_level (Planet*);
	void create_water_body (Planet*, int tile);
	void set_water_bodies (Planet*);
	void set_basins (Planet*);
	void reset_river_directions (Planet*);
	void set_river_directions (Planet*);
	
	double area (const Planet*, const Tile*);
	double distance (const Planet*, const Tile*, const Tile*);
	double find_sea_level (Planet*);
	Vector3 from_lat_long (double, double);
	double latitude (const Vector3&);
	double longitude (const Vector3&);
	double north (const Planet*, const Tile*);
	double radius (const Planet*, const Tile*);
	double circumference (const Planet*);

	const Terrain_tile* tile (const Planet*, int id);
	const Terrain_tile* tile (const Planet*, const Tile*);
	const Terrain_corner* corner (const Planet*, int id);
	const Terrain_corner* corner (const Planet*, const Corner*);
	const Terrain_edge* edge (const Planet*, int id);
	const Terrain_edge* edge (const Planet*, const Edge*);
	Terrain_tile* m_tile (Planet*, int id);
	Terrain_corner* m_corner (Planet*, int id);
	Terrain_edge* m_edge (Planet*, int id);
}

#endif
