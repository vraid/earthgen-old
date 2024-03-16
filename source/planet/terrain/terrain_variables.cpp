#include "terrain_variables.h"
#include "../terrain/terrain.h"

namespace earthgen {

const Vector3& axis (const Terrain& terrain) {return terrain.var.axis;}
double axial_tilt (const Terrain& terrain) {return terrain.var.axial_tilt;}
double radius (const Terrain& terrain) {return terrain.var.radius;}
double sea_level (const Terrain& terrain) {return terrain.var.sea_level;}

}
