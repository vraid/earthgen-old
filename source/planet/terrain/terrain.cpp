#include "terrain.h"
#include "../planet.h"
#include "../../math/quaternion.h"
#include <cmath>

void clear_terrain (Planet& p) {
	std::deque<Terrain_tile>().swap(p.terrain->tiles);
	std::deque<Terrain_corner>().swap(p.terrain->corners);
	std::deque<Terrain_edge>().swap(p.terrain->edges);
}

void init_terrain (Planet& p) {
	clear_terrain(p);
	p.terrain->tiles.resize(tile_count(p));
	p.terrain->corners.resize(corner_count(p));
	p.terrain->edges.resize(edge_count(p));
}

double latitude (const Vector3& v) {
	return std::asin(v.z);
}
double longitude (const Vector3& v) {
	if (v.x == 0 && v.y == 0)
		return 0;
	return std::atan2(v.y, v.x);
}

double latitude (const Planet& p, const Vector3& v) {
	return pi/2 - angle(axis(p), v);
}

double longitude (const Planet& p, const Vector3& v) {
	Vector3 u = rotation_to_default(p) * v;
	return longitude(u);
}

double north (const Planet& p, const Tile* t) {
	Vector3 v = reference_rotation(t, rotation_to_default(p)) * vector(nth_tile(t, 0));
	return pi-atan2(v.y, v.x);
}

double area (const Planet& p, const Tile* t) {
	double a = 0.0;
	for (int k=0; k<edge_count(t); k++) {
		double angle = acos(dot_product(normal(vector(t) - vector(nth_corner(t,k))), normal(vector(t) - vector(nth_corner(t,k+1)))));
		a += 0.5 * sin(angle) * distance(vector(t), vector(nth_corner(t,k))) * distance(vector(t), vector(nth_corner(t,k+1)));
		/*
		 *	double base = length(corner(t,k)->v - corner(t,k+1)->v);
		 *	double height = length(((corner(t,k)->v + corner(t,k+1)->v) * 0.5) - t->v);
		 *	a += 0.5 * base * height;
		 */
	}
	return a * pow(radius(p), 2.0);
}

double length (const Planet& p, const Edge* e) {
	return distance(vector(nth_corner(e,0)), vector(nth_corner(e,1))) * radius(p);
}

double angular_velocity (const Planet&) {
	/* currently locked at 24 hours */
	return 2.0 * pi / (24 * 60 * 60);
}

double coriolis_coefficient (const Planet& p, double latitude) {
	return 2.0 * angular_velocity(p) * sin(latitude);
}

Vector3 default_axis () {return Vector3(0,0,1);}
Quaternion rotation (const Planet& p) {
	return Quaternion(default_axis(), axis(p));
}
Quaternion rotation_to_default (const Planet& p) {
	return conjugate(rotation(p));
	return Quaternion(axis(p), default_axis());
}

const Terrain& terrain (const Planet& p) {return *p.terrain;}
Terrain& m_terrain (Planet& p) {return *p.terrain;}

const std::deque<Terrain_tile>& tiles (const Terrain& t) {return t.tiles;}
const std::deque<Terrain_corner>& corners (const Terrain& t) {return t.corners;}
const std::deque<Terrain_edge>& edges (const Terrain& t) {return t.edges;}

const Terrain_tile& nth_tile (const Terrain& t, int n) {return t.tiles[n];}
const Terrain_corner& nth_corner (const Terrain& t, int n) {return t.corners[n];}
const Terrain_edge& nth_edge (const Terrain& t, int n) {return t.edges[n];}

Terrain_tile& m_tile (Terrain& t, int n) {return t.tiles[n];}
Terrain_corner& m_corner (Terrain& t, int n) {return t.corners[n];}
Terrain_edge& m_edge (Terrain& t, int n) {return t.edges[n];}
