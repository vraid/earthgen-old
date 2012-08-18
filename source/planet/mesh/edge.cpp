#include "edge.h"

namespace mesh {

const Corner* corner (const Edge* e, int i) {
	int n = i%2;
	if (n < 0) n += 2;
	return e->corner[n];
}

int sign (const Edge* e, const Corner* c) {
	int n = 0;
	if (e->corner[0] == c) n = 1;
	else if (e->corner[1] == c) n = -1;
	return n;
}

int sign (const Edge* e, const Tile* t) {
	int n = 0;
	if (e->tile[0] == t) n = 1;
	else if (e->tile[1] == t) n = -1;
	return n;
}

const Tile* tile (const Edge* e, int i) {
	int n = i%2;
	if (n < 0) n += 2;
	return e->tile[n];
}
}
