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

const Terrain& terrain (const Planet&);
Terrain& m_terrain (Planet&);

const std::deque<Terrain_tile>& tiles (const Terrain&);
const std::deque<Terrain_corner>& corners (const Terrain&);
const std::deque<Terrain_edge>& edges (const Terrain&);

const Terrain_tile& nth_tile (const Terrain&, int);
const Terrain_corner& nth_corner (const Terrain&, int);
const Terrain_edge& nth_edge (const Terrain&, int);

Terrain_tile& m_tile (Terrain&, int);
Terrain_corner& m_corner (Terrain&, int);
Terrain_edge& m_edge (Terrain&, int);


#endif
