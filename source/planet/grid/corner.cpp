#include "corner.h"

Corner::Corner (int i) :
	id (i) {
	for (auto& t : tiles)
		t = nullptr;
	for (auto& c : corners)
		c = nullptr;
	for (auto& e : edges)
		e = nullptr;
}

int position (const Corner& c, const Tile* t) {
	for (int i=0; i<3; i++)
		if (c.tiles[i] == t)
			return i;
	return -1;
}
int position (const Corner& c, const Corner* n) {
	for (int i=0; i<3; i++)
		if (c.corners[i] == n)
			return i;
	return -1;
}
int position (const Corner& c, const Edge* e) {
	for (int i=0; i<3; i++)
		if (c.edges[i] == e)
			return i;
	return -1;
}

int id (const Corner& c) {return c.id;}
const Vector3& vector (const Corner& c) {return c.v;}
const std::array<const Tile*, 3>& tiles (const Corner& c) {return c.tiles;}
const std::array<const Corner*, 3>& corners (const Corner& c) {return c.corners;}
const std::array<const Edge*, 3>& edges (const Corner& c) {return c.edges;}

const Corner* nth_corner (const Corner& c, int i) {
	int k = i < 0 ?
		i%3 + 3 :
		i%3;
	return c.corners[k];
}
const Edge* nth_edge (const Corner& c, int i) {
	int k = i < 0 ?
		i%3 + 3 :
		i%3;
	return c.edges[k];
}
