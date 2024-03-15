#include "corner.h"

namespace earthgen {

Corner::Corner (int i) :
	id (i),
	tiles ({nullptr, nullptr, nullptr}),
	corners ({nullptr, nullptr, nullptr}),
	edges ({nullptr, nullptr, nullptr}) {}

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

int position (const Corner& c, const Tile* t) {
	for (int i=0; i<3; i++) {
		if (c.tiles[i] == t) {
			return i;
		}
	}
	return -1;
}
int position (const Corner& c, const Corner* n) {
	for (int i=0; i<3; i++) {
		if (c.corners[i] == n) {
			return i;
		}
	}
	return -1;
}
int position (const Corner& c, const Edge* e) {
	for (int i=0; i<3; i++) {
		if (c.edges[i] == e) {
			return i;
		}
	}
	return -1;
}

}
