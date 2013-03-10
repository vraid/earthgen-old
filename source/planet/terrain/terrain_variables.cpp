#include "terrain_variables.h"
#include "../planet.h"

const Vector3& axis (const Planet& p) {return p.terrain.var.axis;}
double axial_tilt (const Planet& p) {return p.terrain.var.axial_tilt;}
double radius (const Planet& p) {return p.terrain.var.radius;}
double sea_level (const Planet& p) {return p.terrain.var.sea_level;}