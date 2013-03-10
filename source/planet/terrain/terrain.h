#ifndef terrain_h
#define terrain_h

#include <deque>
#include "terrain_tile.h"
#include "terrain_corner.h"
#include "terrain_edge.h"
#include "terrain_variables.h"
#include "river.h"
class Planet;
class Tile;
class Quaternion;

class Terrain {
public:
	Terrain () {}
	
	Terrain_variables var;
	std::deque<Terrain_tile> tiles;
	std::deque<Terrain_corner> corners;
	std::deque<Terrain_edge> edges;
};

void clear_terrain (Planet&);
void init_terrain (Planet&);

double latitude (const Vector3&);
double longitude (const Vector3&);

double latitude (const Planet&, const Vector3&);
double longitude (const Planet&, const Vector3&);

// angle from corner 0 to north
double north (const Planet&, const Tile*);

double area (const Planet&, const Tile*);
double length (const Planet&, const Edge*);

double coriolis_coefficient (const Planet&, double);

Vector3 default_axis ();
Quaternion rotation (const Planet&);
// rotation to bring planet axis into default position
Quaternion rotation_to_default (const Planet&);

const std::deque<Terrain_tile>& terrain_tiles (const Planet&);
const std::deque<Terrain_corner>& terrain_corners (const Planet&);
const std::deque<Terrain_edge>& terrain_edges (const Planet&);

const Terrain_tile& nth_terrain_tile (const Planet&, int);
const Terrain_corner& nth_terrain_corner (const Planet&, int);
const Terrain_edge& nth_terrain_edge (const Planet&, int);

Terrain_tile& m_terrain_tile (Planet&, int);
Terrain_corner& m_terrain_corner (Planet&, int);
Terrain_edge& m_terrain_edge (Planet&, int);


#endif
