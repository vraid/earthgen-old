#include "edge.h"

Edge::Edge (int i) :
	id (i) {
	for (auto& t : tiles)
		t = nullptr;
	for (auto& c : corners)
		c = nullptr;
}

int position (const Edge& e, const Tile* t) {
	if (e.tiles[0] == t)
		return 0;
	else if (e.tiles[1] == t)
		return 1;
	return -1;
}
int position (const Edge& e, const Corner* c) {
	if (e.corners[0] == c)
		return 0;
	else if (e.corners[1] == c)
		return 1;
	return -1;
}

int sign (const Edge& e, const Tile* t) {
	if (e.tiles[0] == t)
		return 1;
	else if (e.tiles[1] == t)
		return -1;
	return 0;
}
int sign (const Edge& e, const Corner* c) {
	if (e.corners[0] == c)
		return 1;
	else if (e.corners[1] == c)
		return -1;
	return 0;
}

int id (const Edge& e) {return e.id;}
const std::array<const Tile*, 2>& tiles (const Edge& e) {return e.tiles;}
const std::array<const Corner*, 2>& corners (const Edge& e) {return e.corners;}
const Tile* nth_tile (const Edge& e, int i) {
	return e.tiles[i];
}
const Corner* nth_corner (const Edge& e, int i) {
	return e.corners[i];
}
