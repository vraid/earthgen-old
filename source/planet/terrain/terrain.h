#ifndef terrain_h
#define terrain_h

#include <vector>
#include "terrain_tile.h"
#include "terrain_corner.h"
#include "terrain_edge.h"
#include "../../math/vector3.h"

namespace earthgen {

class Tile;
class Edge;
class Grid;
class Quaternion;

class Terrain_variables {
public:
	Terrain_variables () {}

	Vector3 axis;
	double axial_tilt;
	double radius;
	double sea_level;
};

class Terrain {
public:
	Terrain () {}
	
	Terrain_variables var;
	std::vector<Terrain_tile> tiles;
	std::vector<Terrain_corner> corners;
	std::vector<Terrain_edge> edges;
};

void clear_terrain (Terrain&);
void init_terrain (Terrain&, const Grid&);

double latitude (const Vector3&);
double longitude (const Vector3&);

double latitude (const Terrain&, const Vector3&);
double longitude (const Terrain&, const Vector3&);

// angle from corner 0 to north
double north (const Terrain&, const Tile*);

double area (const Terrain&, const Tile*);
double length (const Terrain&, const Edge*);

double coriolis_coefficient (const Terrain&, double);

Vector3 default_axis ();
Quaternion rotation (const Terrain&);
// rotation to bring planet axis into default position
Quaternion rotation_to_default (const Terrain&);

const std::vector<Terrain_tile>& tiles (const Terrain&);
const std::vector<Terrain_corner>& corners (const Terrain&);
const std::vector<Terrain_edge>& edges (const Terrain&);

const Terrain_tile& nth_tile (const Terrain&, int);
const Terrain_corner& nth_corner (const Terrain&, int);
const Terrain_edge& nth_edge (const Terrain&, int);

Terrain_tile& m_tile (Terrain&, int);
Terrain_corner& m_corner (Terrain&, int);
Terrain_edge& m_edge (Terrain&, int);

inline const Vector3& axis (const Terrain& terrain) {return terrain.var.axis;}
inline double axial_tilt (const Terrain& terrain) {return terrain.var.axial_tilt;}
inline double radius (const Terrain& terrain) {return terrain.var.radius;}
inline double sea_level (const Terrain& terrain) {return terrain.var.sea_level;}

}

#endif
