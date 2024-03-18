#include "edge.h"

namespace earthgen {

Edge::Edge (int i) :
	id (i),
	tiles ({nullptr, nullptr}),
	corners ({nullptr, nullptr}) {}

std::array<int,2> edge_index_array {0, 1};

const std::array<int,2>& edge_indices () {
	return edge_index_array;
}

int position (const Edge& e, const Tile* t) {
	if (e.tiles[0] == t) {
		return 0;
	}
	else if (e.tiles[1] == t) {
		return 1;
	}
	return -1;
}
int position (const Edge& e, const Corner* c) {
	if (e.corners[0] == c) {
		return 0;
	}
	else if (e.corners[1] == c) {
		return 1;
	}
	return -1;
}

int sign (const Edge& e, const Tile* t) {
	if (e.tiles[0] == t) {
		return 1;
	}
	else if (e.tiles[1] == t) {
		return -1;
	}
	return 0;
}
int sign (const Edge& e, const Corner* c) {
	if (e.corners[0] == c) {
		return 1;
	}
	else if (e.corners[1] == c) {
		return -1;
	}
	return 0;
}

}
