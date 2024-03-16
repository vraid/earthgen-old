#ifndef terrain_variables_h
#define terrain_variables_h

#include "../../math/vector3.h"

namespace earthgen {

class Terrain;

class Terrain_variables {
public:
	Terrain_variables () {}

	Vector3 axis;
	double axial_tilt;
	double radius;
	double sea_level;
};

const Vector3& axis (const Terrain&);
double axial_tilt (const Terrain&);
double radius (const Terrain&);
double sea_level (const Terrain&);

}

#endif
