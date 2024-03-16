#ifndef terrain_generation_h
#define terrain_generation_h

#include <vector>
#include <array>
#include "../../math/vector3.h"
#include "terrain_parameters.h"

namespace earthgen {

class Tile;
class Corner;
class Edge;
class Grid;
class Terrain;

void generate_terrain (Terrain&, Grid&, const Terrain_parameters&);

void _set_variables (Terrain&, const Terrain_parameters&);
void _set_elevation (Terrain&, const Grid&, const Terrain_parameters&);
void _scale_elevation (Terrain&, const Grid&, const Terrain_parameters&);
void _create_sea (Terrain&, const Grid&, const Terrain_parameters&);
std::vector<std::array<Vector3, 3> > _elevation_vectors (const Terrain_parameters&);

int _tile_type (const Terrain&, const Tile*);
int _corner_type (const Terrain&, const Corner*);
int _edge_type (const Terrain&, const Edge*);
void _classify_terrain (Terrain&, const Grid&);

float _elevation_at_point (const Vector3&, const std::vector<std::array<Vector3, 3> >&);

//returns point on sphere of uniform distribution, given two random integers
Vector3 point_uniform (int, int);

}

#endif
