#include "terrain_tile.h"

bool is_land (const Terrain_tile& t) {return t.type & t.type_land;}
bool is_water (const Terrain_tile& t) {return t.type & t.type_water;}
bool has_coast (const Terrain_tile& t) {return t.type & t.type_coast;}

float elevation (const Terrain_tile& t) {return t.elevation;}
float water_depth (const Terrain_tile& t) {return t.water.depth;}