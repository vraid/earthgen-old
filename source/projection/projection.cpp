#include "projection.h"
#include "../planet/planet.h"
#include <math.h>
#include <iostream>

namespace projection {

void create_geometry (Projection* proj) {
	const Planet* p = proj->p;
	proj->tile.clear();
	proj->tile.resize(7*mesh::tiles(p));
	for (int i=0; i<mesh::tiles(p); i++) {
		const Tile* t = mesh::tile(p,i);
		proj->tile[7*i] = to_hammer(t->v);
		for (int k=0; k<6; k++) {
			proj->tile[7*i+k+1] = to_hammer(mesh::corner(t,k)->v);
			if (t->v.x < 0 && flip(proj->tile[7*i], proj->tile[7*i+k+1])) {
				proj->tile[7*i+k+1].x *= -1;
			}
		}
	}
	proj->north_id = mesh::select_tile(p,Vector3(0,0,1))->id;
	proj->south_id = mesh::select_tile(p,Vector3(0,0,-1))->id;
	for (int i=0; i<6; i++) {
		const Vector3 v = mesh::corner(mesh::tile(p,proj->north_id),i)->v;
		if (v.x == 0 && v.y == 0) {
			proj->north_id = -1;
			break;
		}
	}
	for (int i=0; i<6; i++) {
		const Vector3 v = mesh::corner(mesh::tile(p,proj->south_id),i)->v;
		if (v.x == 0 && v.y == 0) {
			proj->south_id = -1;
			break;
		}
	}
	
	proj->north_tile.clear();
	proj->south_tile.clear();
	if (proj->north_id >= 0) {
		const Tile* t = mesh::tile(p,proj->north_id);
		int first = 0;
		for (int i=0; i<6; i++) {
			const Corner* c = mesh::corner(t,i);
			for (int k=0; k<3; k++) {
				if (mesh::tile(c,k) != t && mesh::tile(c,k)->v.x < 0 && c->v.y * mesh::tile(c,k)->v.y < 0) {
					first = i;
					break;
				}
			}
		}
		proj->north_tile.push_back(to_hammer(t->v));
		std::cout << "north tile: ";
		for (int i=first; i<=first+t->edges; i++) {
			proj->north_tile.push_back(to_hammer(mesh::corner(t,i)->v));
			std::cout << "(" << mesh::corner(t,i)->v.x << ", " << mesh::corner(t,i)->v.y << "), ";
		}
		std::cout << std::endl;
		if (flip(proj->north_tile[1], proj->north_tile[2])) {
			proj->north_tile[1].x *= -1;
		}
		else {
			proj->north_tile[proj->north_tile.size()-1].x *= -1;
		}
//		proj->north_tile.push_back(to_hammer(Vector3(0,0,1)));
		for (int i=proj->north_id*7; i<proj->north_id*7+7; i++)
			proj->tile[i] = Vector2(0,0);
	}
	
	if (proj->south_id >= 0) {
		const Tile* t = mesh::tile(p,proj->south_id);
		int first = 0;
		for (int i=0; i<6; i++) {
			const Corner* c = mesh::corner(t,i);
			for (int k=0; k<3; k++) {
				if (mesh::tile(c,k) != t && mesh::tile(c,k)->v.x < 0 && c->v.y * mesh::tile(c,k)->v.y < 0) {
					first = i;
				}
			}
		}
		proj->south_tile.push_back(to_hammer(t->v));
		std::cout << "south tile: ";
		for (int i=first; i<=first+t->edges; i++) {
			proj->south_tile.push_back(to_hammer(mesh::corner(t,i)->v));
			std::cout << "(" << mesh::corner(t,i)->v.x << ", " << mesh::corner(t,i)->v.y << ")";
		}
		std::cout << std::endl;
		if (flip(proj->south_tile[1], proj->south_tile[2])) {
			proj->south_tile[1].x *= -1;
		}
		else {
			proj->south_tile[proj->south_tile.size()-1].x *= -1;
		}
//		proj->south_tile.push_back(to_hammer(Vector3(0,0,-1)));
		for (int i=proj->south_id*7; i<proj->south_id*7+7; i++)
			proj->tile[i] = Vector2(0,0);
	}
}

bool flip (const Vector2& v, const Vector2& e) {
	return (v.x * e.x < 0);
}

bool flip (const Vector3& v, const Vector3& e) {
	return (v.x < 0 && v.y * e.y <= 0);
}

Vector3 from_hammer (const Vector2& v) {
	double z = sqrt(1.0-pow(v.x/4.0,2.0)-pow(v.y/2.0,2.0));
	double latitude = asin(z*v.y);
	double longitude = 2.0*atan(z*v.x / (2.0*(2.0*z*z-1.0)));
	Vector3 vec = terrain::from_lat_long(latitude, longitude);
	return vec;
}

void init (Planet* p, Projection* proj) {
	proj->p = p;
	proj->color.resize(mesh::tiles(p)*3);
	create_geometry(proj);
}

void set_colors (Projection* proj) {
	Planet* p = proj->p;
	float water_deep[3] = {0.01,0.03,0.18};
	float water_surface[3] = {0.03,0.26,0.51};
	float land[3] = {0.8,0.7,0.59};
	float land_max[3] = {0.53,0.48,0.29};
	for (int i=0; i<mesh::tiles(p); i++) {
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

Vector2 to_hammer (const Vector3& v) {
	double latitude = terrain::latitude(v);
	double longitude = terrain::longitude(v);
	Vector2 proj = Vector2();
	proj.x = 2.0*sqrt(2.0)*cos(latitude)*sin(longitude/2.0) / sqrt(1.0+cos(latitude)*cos(longitude/2.0));
	proj.y = sqrt(2.0)*sin(latitude) / sqrt(1.0+cos(latitude)*cos(longitude/2.0));
	return proj;
}

double hammer_width (double y) {
	return 2.0*sqrt(2.0)*cos(y);
}

double hammer_height (double x) {
	return sqrt(2.0)*cos(2.0*x);
}

}
