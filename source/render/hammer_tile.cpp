#include "hammer_tile.h"
#include "hammer_projection.h"
#include "../planet/planet.h"
#include "../math/matrix3.h"
#include "../math/quaternion.h"

Hammer_tile::Hammer_tile (const Tile* t, const Matrix3& m) {
	centre = to_hammer(m * vector(t));
	double tile_longitude = longitude(m * vector(t));
	Quaternion longitude_offset = Quaternion(Vector3(0,0,1), -longitude(m * vector(t)));
	for (int i=0; i < edge_count(t); i++) {
		const Vector3 v = m * vector(t->corners[i]);
		corners[i] = to_hammer(latitude(v), tile_longitude + longitude(longitude_offset * v));
	}
	if (edge_count(t) == 5)
		corners[5] = corners[0];
}