#include "terrain_edge.h"

bool is_land (const Terrain_edge& e) {return e.type == e.type_land;}
bool is_water (const Terrain_edge& e) {return e.type == e.type_water;}
bool is_coast (const Terrain_edge& e) {return e.type == e.type_coast;}