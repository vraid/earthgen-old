#include "projection.h"
#include "../planet/planet.h"
#include <math.h>
#include <iostream>

namespace projection {

void init (const Planet* p, Projection* proj) {
	proj->p = p;
	proj->color.resize(grid::tiles(p)*3);
	proj->tile_center.resize(grid::tiles(p));
	proj->tile_corner.resize(grid::tiles(p)*6);
}

void reset_geometry (Projection* proj) {
	proj->color.assign(grid::tiles(proj->p)*3, 0);
	proj->tile_center.assign(grid::tiles(proj->p), Vector2(0,0));
	proj->tile_corner.assign(grid::tiles(proj->p)*6, Vector2(0,0));
	proj->north_tile = -1;
	proj->south_tile = -1;
	proj->north_face = -1;
	proj->south_face = -1;
}

void create_geometry (Projection* proj, const Quaternion& q) {
	reset_geometry(proj);
	
	const Planet* p = proj->p;

//	set_north_tile(proj, q);
//	set_south_tile(proj, q);

	for (int i=0; i<grid::tiles(p); i++) {
		if (i != proj->north_tile && i != proj->south_tile) {
			set_tile_geometry(proj, q, i);
		}
	}
}

void set_tile_geometry (Projection* proj, const Quaternion& q, int i) {
	proj->tile_center[i] = to_hammer(q*grid::tile(proj->p,i)->v);
	for (int k=0; k<6; k++) {
		double latitude = terrain::latitude(q*grid::corner(grid::tile(proj->p,i),k)->v);
		double longitude = terrain::longitude(q*grid::corner(grid::tile(proj->p,i),k)->v);
		Vector2 v = to_hammer(latitude, longitude);
		
		if (opposite_sides(proj->tile_center[i], v)) {
			Vector2 left = left_position(latitude, longitude);
			Vector2 right = right_position(latitude, longitude);
			if (vector2::length(proj->tile_center[i]-left) < vector2::length(proj->tile_center[i]-right)) {
				proj->tile_corner[i*6+k] = left;
			}
			else proj->tile_corner[i*6+k] = right;
		}
		else proj->tile_corner[i*6+k] = v;
	}
}

void set_north_tile (Projection* proj, const Quaternion& q) {
	const Tile* t = grid::select_tile(proj->p, q*Vector3(0,0,1));
	proj->north_tile = t->id;
}

void set_south_tile (Projection* proj, const Quaternion& q) {
	const Tile* t = grid::select_tile(proj->p, q*Vector3(0,0,-1));
	proj->south_tile = t->id;
}

Vector2 left_position (double latitude, double longitude) {
	if (longitude >= 0) return to_hammer(latitude, longitude);
	return to_hammer(latitude, 2*pi+longitude);
}

Vector2 right_position (double latitude, double longitude) {
	if (longitude <= 0) return to_hammer(latitude, longitude);
	return to_hammer(latitude, 2*pi+longitude);
}

bool opposite_sides (const Vector2& v, const Vector2& e) {
	return (v.x * e.x < 0);
}

void set_colors (Projection* proj) {
	const Planet* p = proj->p;
	float water_deep[3] = {0.01,0.03,0.18};
	float water_surface[3] = {0.03,0.26,0.51};
	float land[3] = {0.8,0.7,0.59};
	float land_max[3] = {0.53,0.48,0.29};
	for (int i=0; i<grid::tiles(p); i++) {
		const Terrain_tile* t = terrain::tile(p,i);
		if (t->is_water) {
			float d = std::min(1.0, 8.0*t->water.depth/(p->terrain->var.sea_level - p->terrain->var.lowest_point));
			proj->color[3*i] = d*water_deep[0] + (1-d)*water_surface[0];
			proj->color[3*i+1] = d*water_deep[1] + (1-d)*water_surface[1];
			proj->color[3*i+2] = d*water_deep[2] + (1-d)*water_surface[2];
		}
		else {
			float d = std::min(1.0, 2.5*(t->elevation - p->terrain->var.sea_level)/(p->terrain->var.highest_point - p->terrain->var.sea_level));
			proj->color[3*i] = d*land_max[0] + (1-d)*land[0];
			proj->color[3*i+1] = d*land_max[1] + (1-d)*land[1];
			proj->color[3*i+2] = d*land_max[2] + (1-d)*land[2];
		}
	}
}

void color_topography (Projection* proj) {
	const Planet* p = proj->p;
	static const float w[5] = {-5000.0, -4000.0, -3000.0, -2000.0, -1000.0};
	static float water[6][3] = {
		{0.0, 0.0, 0.3},
		{0.0, 0.0, 0.4},
		{0.0, 0.0, 0.5},
		{0.0, 0.0, 0.6},
		{0.0, 0.1, 0.8},
		{0.1, 0.3, 0.6}};
	static float l[5] = {1000.0, 2000.0, 3000.0, 4000.0};
	static float land[5][3] = {
		{0.9, 0.7, 0.3},
		{0.8, 0.6, 0.3},
		{0.7, 0.5, 0.1},
		{0.3, 0.2, 0.0},
		{0.1, 0.1, 0.0}};
	for (int i=0; i<grid::tiles(p); i++) {
		const Terrain_tile* t = terrain::tile(p,i);
		float e = t->elevation - p->terrain->var.sea_level;
		if (t->is_water) {
			for (int k=0; k<6; k++) {
				if (k == 5 || e <= w[k]) {
					proj->color[3*i]   = water[k][0];
					proj->color[3*i+1] = water[k][1];
					proj->color[3*i+2] = water[k][2];
					break;
				}
			}
		}
		else {
			for (int k=0; k<5; k++) {
				if (k == 4 || e <= l[k]) {
					proj->color[3*i]   = land[k][0];
					proj->color[3*i+1] = land[k][1];
					proj->color[3*i+2] = land[k][2];
					break;
				}
			}
		}
	}
}

Vector3 from_hammer (const Vector2& v) {
	double z = sqrt(1.0-pow(v.x/4.0,2.0)-pow(v.y/2.0,2.0));
	double latitude = asin(z*v.y);
	double longitude = 2.0*atan(z*v.x / (2.0*(2.0*z*z-1.0)));
	return terrain::from_lat_long(latitude, longitude);
}

Vector2 to_hammer (const Vector3& v) {
	double latitude = terrain::latitude(v);
	double longitude = terrain::longitude(v);
	return to_hammer(latitude, longitude);
}

Vector2 to_hammer (double latitude, double longitude) {
//	x = sqrt(8.0)*cos(latitude)*sin(longitude/2.0) / sqrt(1.0+cos(latitude)*cos(longitude/2.0));
//	y = sqrt(2.0)*sin(latitude) / sqrt(1.0+cos(latitude)*cos(longitude/2.0));
	return Vector2(2.0*cos(latitude)*sin(longitude/2.0), sin(latitude)) * (sqrt(2.0)/sqrt(1.0+cos(latitude)*cos(longitude/2.0)));
}

double hammer_width (double y) {
//	return sqrt(8.0)*sqrt(1.0-y*y/2.0);
	return sqrt(8.0*(1.0-y*y/2.0));
}

double hammer_height (double x) {
//	return sqrt(2.0)*sqrt(1.0-x*x/8.0);
	return sqrt(2.0*(1.0-x*x/8.0));
}

}
