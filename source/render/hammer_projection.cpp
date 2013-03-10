#include "hammer_projection.h"
#include "../math/vector2.h"
#include "../math/vector3.h"
#include "../math/matrix3.h"
#include "../math/quaternion.h"
#include "../planet/planet.h"
#include <cmath>

void clear (Hammer_projection& proj) {
	std::deque<Hammer_tile>().swap(proj.tiles);
}

void create_geometry (Hammer_projection& proj, const Planet& p, const Quaternion& q) {
	clear(proj);
	Matrix3 m = matrix3(q);
	for (auto& t : tiles(p)) {
		proj.tiles.push_back(Hammer_tile(&t, m));
	}
}

Vector3 from_lat_long(double latitude, double longitude) {
	return Vector3(std::cos(latitude) * std::cos(longitude), std::cos(latitude) * std::sin(longitude), std::sin(latitude));
}

Vector3 from_hammer (const Vector2& v) {
	double z = sqrt(1.0-pow(v.x/4.0,2.0)-pow(v.y/2.0,2.0));
	double latitude = asin(z*v.y);
	double longitude = 2.0*atan(z*v.x / (2.0*(2.0*z*z-1.0)));
	return from_lat_long(latitude, longitude);
}
Vector2 to_hammer (const Vector3& v) {
	return to_hammer(latitude(v), longitude(v));
}
Vector2 to_hammer (double latitude, double longitude) {
	return Vector2(2.0*cos(latitude)*sin(longitude/2.0), sin(latitude)) * (sqrt(2.0)/sqrt(1.0+cos(latitude)*cos(longitude/2.0)));
}

double hammer_width () {return sqrt(8.0);}
double hammer_height () {return sqrt(2.0);}