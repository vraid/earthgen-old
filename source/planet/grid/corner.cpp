#include "corner.h"

namespace grid {

const Corner* corner (const Corner* c, int i) {
	int n = i%3;
	if (n < 0) n += 3;
	return c->corner[n];
}

const Edge* edge (const Corner* c, int i) {
	int n = i%3;
	if (n < 0) n += 3;
	return c->edge[n];
}

int position (const Corner* c, const Corner* e) {
	int n = -1;
	for (int i=0; i<3; i++) {
		if (c->corner[i] == e) {
			n = i;
			break;
		}
	}
	return n;
}

int position (const Corner* c, const Edge* e) {
	int n = -1;
	for (int i=0; i<3; i++) {
		if (c->edge[i] == e) {
			n = i;
			break;
		}
	}
	return n;
}

int position (const Corner* c, const Tile* t) {
	int n = -1;
	for (int i=0; i<3; i++) {
		if (c->tile[i] == t) {
			n = i;
			break;
		}
	}
	return n;
}

const Tile* tile (const Corner* c, int i) {
	int n = i%3;
	if (n < 0) n += 3;
	return c->tile[n];
}

}
