#include "hammer_projection.h"
#include "../math/vector2.h"
#include "../math/vector3.h"
#include "../math/matrix3.h"
#include "../math/quaternion.h"
#include "../grid/grid.h"
#include "../terrain/terrain.h"
#include <cmath>

namespace earthgen {

void clear (Hammer_projection& proj) {
	std::vector<Hammer_tile>().swap(proj.tiles);
}

void create_geometry (Hammer_projection& proj, const Grid& grid, const Quaternion& q) {
	clear(proj);
	Matrix3 m = matrix3(q);
	for (auto& t : tiles(grid)) {
		proj.tiles.push_back(Hammer_tile(&t, m));
	}
}

Vector3 from_lat_long(double latitude, double longitude) {
	return Vector3(std::cos(latitude) * std::cos(longitude), std::cos(latitude) * std::sin(longitude), std::sin(latitude));
}

Vector3 from_hammer (const Vector2& v) {
	double z = std::sqrt(1.0-std::pow(v.x()/4.0,2.0)-std::pow(v.y()/2.0,2.0));
	double latitude = std::asin(z*v.y());
	double longitude = 2.0*std::atan(z*v.x() / (2.0*(2.0*z*z-1.0)));
	return from_lat_long(latitude, longitude);
}

Vector2 to_hammer (const Vector3& v) {
	return to_hammer(latitude(v), longitude(v));
}

Vector2 to_hammer (double latitude, double longitude) {
	double x = 2.0 * std::cos(latitude) * std::sin(longitude/2.0);
	double y = std::sin(latitude);
	double scale = (std::sqrt(2.0)/std::sqrt(1.0 + std::cos(latitude) * std::cos(longitude/2.0)));
	return Vector2(x, y) * scale;
}

double hammer_width () {return std::sqrt(8.0);}
double hammer_height () {return std::sqrt(2.0);}

}
