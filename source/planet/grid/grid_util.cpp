#include "grid_util.h"
#include "grid.h"
#include "../../math/math_common.h"
#include "../../math/vector2.h"
#include "../../math/vector3.h"
#include "../../math/quaternion.h"

namespace earthgen {

Quaternion reference_rotation (const Tile* t, Quaternion d) {
	Vector3 v = d * vector(t);
	Quaternion h = Quaternion();
	if (v.x() != 0 || v.y() != 0) {
		if (v.y() != 0) {h = rotation_between(normal(Vector3(v.x(), v.y(), 0)), Vector3(-1,0,0));}
		else if (v.x() > 0) {h = rotation_around(Vector3(0,0,1), pi);}
	}
	Quaternion q = Quaternion();
	if (v.x() == 0 && v.y() == 0) {
		if (v.z() < 0) {q = rotation_around(Vector3(1,0,0), pi);}
	}
	else {
		q = rotation_between(h*v, Vector3(0,0,1));
	}
	return q*h*d;
}

std::vector<Vector2> polygon (const Tile* t, Quaternion d) {
	std::vector<Vector2> p;
	Quaternion q = reference_rotation(t, d);
	for (int i : indices(t)) {
		Vector3 c = q * vector(nth_corner(t, i));
		p.push_back(Vector2(c.x(), c.y()));
	}
	return p;
}

}
