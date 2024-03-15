#include "terrain_corner.h"

namespace earthgen {

bool is_land (const Terrain_corner& c) {return c.type == c.type_land;}
bool is_water (const Terrain_corner& c) {return c.type == c.type_water;}
bool is_coast (const Terrain_corner& c) {return c.type == c.type_coast;}

float elevation (const Terrain_corner& c) {return c.elevation;}
int distance_to_sea (const Terrain_corner& c) {return c.distance_to_sea;}

}
