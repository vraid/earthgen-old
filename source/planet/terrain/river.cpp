#include "river.h"
#include "../planet.h"
#include "../grid/grid.h"

bool has_river (const Planet& p, const Edge* e) {
	const Corner* first = nth_corner(e, 0);
	const Corner* second = nth_corner(e, 1);
	if (river_direction(nth_corner(terrain(p), first->id)) == position(first, second)) return true;
	if (river_direction(nth_corner(terrain(p), second->id)) == position(second, first)) return true;
	return false;
}

const River river (const Planet& p, const Edge* e) {
	River r;
	r.channel = e;
	const Corner* first = nth_corner(e, 0);
	const Corner* second = nth_corner(e, 1);
	if (river_direction(nth_corner(terrain(p), first->id)) == position(first, second)) {
		r.source = first;
		r.direction = second;
	}
	else if (river_direction(nth_corner(terrain(p), second->id)) == position(second, first)) {
		r.source = second;
		r.direction = first;
	}
	return r;
}

const River river (const Planet& p, const Corner* c) {
	River r;
	r.source = c;
	r.direction = nth_corner(c, river_direction(nth_corner(terrain(p), c->id)));
	r.channel = nth_edge(c, river_direction(nth_corner(terrain(p), c->id)));
	return r;
}

const Corner* left_tributary (const Planet& p, const River& r) {
	const Corner* c = nullptr;
	int pos = position(r.source, r.direction);
	const Corner* t = nth_corner(r.source, pos+1);
	if (river_direction(nth_corner(terrain(p), t->id)) == position(t, r.source))
		c = t;
	return c;
}

const Corner* right_tributary (const Planet& p, const River& r) {
	const Corner* c = nullptr;
	int pos = position(r.source, r.direction);
	const Corner* t = nth_corner(r.source, pos-1);
	if (river_direction(nth_corner(terrain(p), t->id)) == position(t, r.source))
		c = t;
	return c;
}
