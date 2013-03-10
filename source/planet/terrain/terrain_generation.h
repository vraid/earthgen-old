#ifndef terrain_generation_h
#define terrain_generation_h

#include <vector>
#include <array>
#include "../../math/vector3.h"
#include "terrain_parameters.h"
class Planet;
class Tile;
class Corner;
class Edge;

void generate_terrain (Planet&, const Terrain_parameters&);

void _set_variables (Planet&, const Terrain_parameters&);
void _set_elevation (Planet&, const Terrain_parameters&);
void _scale_elevation (Planet&, const Terrain_parameters&);
void _create_sea (Planet&, const Terrain_parameters&);
std::vector<std::array<Vector3, 3> > _elevation_vectors (const Terrain_parameters&);

int _tile_type (const Planet&, const Tile*);
int _corner_type (const Planet&, const Corner*);
int _edge_type (const Planet&, const Edge*);
void _classify_terrain (Planet&);
void _set_river_directions (Planet&);

float _elevation_at_point (const Vector3&, const std::vector<std::array<Vector3, 3> >&);

//returns point on sphere of uniform distribution, given two random integers
Vector3 point_uniform (int, int);

#endif
