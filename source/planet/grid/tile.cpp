#include "tile.h"
#include "corner.h"
#include "../../math/math_common.h"

Tile::Tile (int i, int e) :
	id (i), edge_count (e) {
	tiles.resize(edge_count, nullptr);
	corners.resize(edge_count, nullptr);
	edges.resize(edge_count, nullptr);
}

int position (const Tile& t, const Tile* n) {
	for (int i=0; i<t.edge_count; i++)
		if (t.tiles[i] == n)
			return i;
	return -1;
}

int position (const Tile& t, const Corner* c) {
	for (int i=0; i<t.edge_count; i++)
		if (t.corners[i] == c)
			return i;
	return -1;
}

int position (const Tile& t, const Edge* e) {
	for (int i=0; i<t.edge_count; i++)
		if (t.edges[i] == e)
			return i;
	return -1;
}

int id (const Tile& t) {return t.id;}
int edge_count (const Tile& t) {return t.edge_count;}
const Vector3& vector (const Tile& t) {return t.v;}
const std::vector<const Tile*>& tiles (const Tile& t) {return t.tiles;}
const std::vector<const Corner*>& corners (const Tile& t) {return t.corners;}
const std::vector<const Edge*>& edges (const Tile& t) {return t.edges;}

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

Quaternion reference_rotation (const Tile* t, Quaternion d) {
	Vector3 v = d * vector(t);
	Quaternion h = Quaternion();
	if (v.x != 0 || v.y != 0) {
		if (v.y != 0) h = Quaternion(normal(Vector3(v.x, v.y, 0)), Vector3(-1,0,0));
		else if (v.x > 0) h = Quaternion(Vector3(0,0,1), pi);
	}
	Quaternion q = Quaternion();
	if (v.x == 0 && v.y == 0) {
		if (v.z < 0) q = Quaternion(Vector3(1,0,0), pi);
	}
	else {
		q = Quaternion(h*v, Vector3(0,0,1));
	}
	return q*h*d;
}

std::vector<Vector2> polygon (const Tile* t, Quaternion d) {
	std::vector<Vector2> p;
	Quaternion q = reference_rotation(t, d);
	for (int i=0; i<edge_count(t); i++) {
		Vector3 c = q * vector(nth_corner(t, i));
		p.push_back(Vector2(c.x, c.y));
	}
	return p;
}
