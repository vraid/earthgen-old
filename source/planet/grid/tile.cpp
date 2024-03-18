#include "tile.h"
#include "corner.h"
#include "../../math/math_common.h"

namespace earthgen {

Tile::Tile (int i, int e) :
	id (i), edge_count (e) {
	tiles.resize(edge_count, nullptr);
	corners.resize(edge_count, nullptr);
	edges.resize(edge_count, nullptr);
}

std::vector<int> tile_index_vector_5 {0, 1, 2, 3, 4};
std::vector<int> tile_index_vector_6 {0, 1, 2, 3, 4, 5};

const std::vector<int>& indices (const Tile& t) {
	return edge_count(t) == 5 ? tile_index_vector_5 : tile_index_vector_6;
}

const Tile* nth_tile (const Tile& t, int n) {
	int k = n < 0 ?
		n % edge_count(t) + edge_count(t) :
		n % edge_count(t);
	return t.tiles[k];
}

const Corner* nth_corner (const Tile& t, int n) {
	int k = n < 0 ?
		n % edge_count(t) + edge_count(t) :
		n % edge_count(t);
	return t.corners[k];
}

const Edge* nth_edge (const Tile& t, int n) {
	int k = n < 0 ?
		n % edge_count(t) + edge_count(t) :
		n % edge_count(t);
	return t.edges[k];
}

int position (const Tile& t, const Tile* n) {
	for (int i : indices(t)) {
		if (t.tiles[i] == n) {
			return i;
		}
	}
	return -1;
}

int position (const Tile& t, const Corner* c) {
	for (int i : indices(t)) {
		if (t.corners[i] == c) {
			return i;
		}
	}
	return -1;
}

int position (const Tile& t, const Edge* e) {
	for (int i : indices(t)) {
		if (t.edges[i] == e) {
			return i;
		}
	}
	return -1;
}

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
