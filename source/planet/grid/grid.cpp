#include "grid.h"
#include "../planet.h"
#include "../../math/quaternion.h"
#include "../../math/matrix3.h"
#include <fstream>
#include <stdlib.h>
#include <math.h>

namespace grid {

const Corner* corner (const Planet* p, int i) {
	const Grid* m = p->grid;
	const Corner* c = nullptr;
	if (i >= 0 && i < m->corners) {
		c = &m->corner[i];
	}
	return c;
}

int corners (const Planet* p) {
	return p->grid->corners;
}

const Edge* edge (const Planet* p, int i) {
	const Grid* m = p->grid;
	const Edge* e = nullptr;
	if (i >= 0 && i < m->edges) {
		e = &m->edge[i];
	}
	return e;
}

int edges (const Planet* p) {
	return p->grid->edges;
}

void init (Grid* m, int size) {
	m->size = size;
	m->tiles = (int)(10*pow(3,size)+2);
	m->corners = (int)(20*pow(3,size));
	m->edges = m->tiles + m->corners - 2;
	m->tile.resize(m->tiles);
	m->corner.resize(m->corners);
	m->edge.resize(m->edges);
	for (int i=0; i<m->tiles; i++) {
		m->tile[i].id = i;
		int e = 6;
		if (i < 12) e = 5;
		m->tile[i].edges = e;
	}
	for (int i=0; i<m->corners; i++) {
		m->corner[i].id = i;
	}
	for (int i=0; i<m->edges; i++) {
		m->edge[i].id = i;
	}
}

void rotate (Grid* m, const Quaternion& q) {
	Matrix3 mat = quaternion::matrix(q);
	for (int i=0; i<m->tiles; i++) {
		m->tile[i].v = mat*m->tile[i].v;
	}
	for (int i=0; i<m->corners; i++) {
		m->corner[i].v = mat*m->corner[i].v;
	}
}

const Tile* select_tile (const Planet* p, const Vector3& v) {
	//starting approximation
	const Tile* t = tile(p,0);
	double d = vector3::distance(v, t->v);
	for (int i=1; i<12; i++) {
		if (vector3::distance(v, tile(p,i)->v) < d) {
			t = tile(p,i);
			d = vector3::distance(v, t->v);
		}
	}
	//navigate the grid to find the closest tile
	bool closer = true;
	while(closer) {
		closer = false;
		const Tile* nt = t->tile[0];
		double nd = vector3::distance(v, nt->v);
		for (int i=1; i<t->edges; i++) {
			if (vector3::distance(v, t->tile[i]->v) < nd) {
				nt = t->tile[i];
				nd = vector3::distance(v, nt->v);
			}
		}
		if (nd < d) {
			closer = true;
			t = nt;
			d = nd;
		}
	}
	return t;
}

const Tile* tile (const Planet* p, int i) {
	const Grid* m = p->grid;
	const Tile* t = nullptr;
	if (i >= 0 && i < m->tiles) {
		t = &m->tile[i];
	}
	return t;
}

int tiles (const Planet* p) {
	return p->grid->tiles;
}

}
