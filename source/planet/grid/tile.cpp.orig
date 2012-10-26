#include "tile.h"
#include "grid.h"
#include "../../math/math.h"
#include <cmath>

Tile::Tile () {
	for (int i=0; i<6; i++) {
		tile[i] = nullptr;
		corner[i] = nullptr;
		edge[i] = nullptr;
	}
}

namespace grid {

const Corner* corner (const Tile* t, int i) {
	int n = i%t->edges;
	if (n < 0) n += t->edges;
	return t->corner[n];
}

const Edge* edge (const Tile* t, int i) {
	int n = i%t->edges;
	if (n < 0) n += t->edges;
	return t->edge[n];
}

bool point_in_tile (const Tile* t, const Vector3& v) {
	Quaternion q = reference_rotation(t);
	Vector3 p = vector3::normal(q*v);
	vector<Vector3> pol = polygon(t,q);
	for (int i=0; i<t->edges; i++) {
		if (p.z >= t->corner[i]->v.z) {
			return true;
		}
	}
	return false;
}

vector<Vector3> polygon (const Tile* t) {
	return polygon(t, reference_rotation(t));
}

vector<Vector3> polygon (const Tile* t, const Quaternion& q) {
	vector<Vector3> v;
	for (int i=0; i<t->edges; i++) {
		Vector3 e = q*t->corner[i]->v;
		v.push_back(e);
	}
	return v;
}

int position (const Tile* t, const Corner* c) {
	int n = -1;
	for (int i=0; i<t->edges; i++) {
		if (t->corner[i] == c) {
			n = i;
			break;
		}
	}
	return n;
}

int position (const Tile* t, const Edge* e) {
	int n = -1;
	for (int i=0; i<t->edges; i++) {
		if (t->edge[i] == e) {
			n = i;
			break;
		}
	}
	return n;
}

int position (const Tile* t, const Tile* e) {
	int n = -1;
	for (int i=0; i<t->edges; i++) {
		if (t->tile[i] == e) {
			n = i;
			break;
		}
	}
	return n;
}

Quaternion reference_rotation (const Tile* t) {
	Quaternion h = Quaternion();
	if (t->v.x != 0 || t->v.y != 0) {
		h = Quaternion(pi+atan2(t->v.y, t->v.x), Vector3(0,0,1));
	}
	Quaternion q = Quaternion();
	if (t->v.x == 0 && t->v.y == 0) {
		if (t->v.z < 0) q = Quaternion(pi, Vector3(1,0,0));
	}
	else {
		q = Quaternion(h*t->v, Vector3(0,0,1));
	}
	return h*q;
}

const Tile* tile (const Tile* t, int i) {
	int n = i%t->edges;
	if (n < 0) n += t->edges;
	return t->tile[n];
}

}
