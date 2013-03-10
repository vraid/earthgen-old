#ifndef terrain_variables_h
#define terrain_variables_h

#include "../../math/vector3.h"
class Planet;

class Terrain_variables {
public:
	Terrain_variables () {}

	Vector3 axis;
	double axial_tilt;
	double radius;
	double sea_level;
};

const Vector3& axis (const Planet&);
double axial_tilt (const Planet&);
double radius (const Planet&);
double sea_level (const Planet&);

#endif