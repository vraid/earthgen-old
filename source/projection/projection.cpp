#include "projection.h"
#include "../planet/planet.h"
#include <math.h>

namespace projection {

void create_geometry (Projection* proj) {
	const Planet* p = proj->p;
	proj->tile.clear();
	proj->corner.clear();
	proj->flipped_corner.clear();
	proj->polygon.clear();
	proj->north_tile.clear();
	proj->south_tile.clear();
	proj->tile.resize(mesh::tiles(p));
	for (int i=0; i<mesh::tiles(p); i++) {
		proj->tile[i] = to_hammer(mesh::tile(p,i)->v);
	}
	proj->corner.resize(mesh::corners(p));
	for (int i=0; i<mesh::corners(p); i++) {
		const Corner* c = mesh::corner(p,i);
		proj->corner[i] = to_hammer(c->v);
		if (c->v.x < 0) {
			for (int k=0; k<3; k++) {
				if (flip(proj->corner[i], proj->tile[mesh::tile(c,k)->id])) {
					proj->flipped_corner.insert(std::pair<int,Vector2>(i, Vector2(-proj->corner[i].x, proj->corner[i].y)));
					break;
				}
			}
		}
	}
	proj->polygon.reserve(mesh::tiles(p)*8);
	for (int i=0; i<mesh::tiles(p); i++) {
		const Tile* t = mesh::tile(p,i);
		proj->polygon.push_back(&proj->tile[i]);
		for (int k=0; k<6; k++) {
			int id = mesh::corner(t,k)->id;
			if (t->v.x < 0 && flip(proj->tile[i], proj->corner[id])) {
				proj->polygon.push_back(&proj->flipped_corner.find(id)->second);
			}
			else proj->polygon.push_back(&proj->corner[id]);
		}
		proj->polygon.push_back(proj->polygon[i*8+1]);
	}
	
	proj->north_pole = Vector2(0,1);
	proj->south_pole = Vector2(0,-1);
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
	
	if (proj->north_id >= 0) {
		const Tile* t = mesh::tile(p,proj->north_id);
		proj->north_tile.push_back(&proj->tile[proj->north_id]);
		int first = 0;
		for (int i=0; i<6; i++) {
			int k = mesh::corner(t,i)->id;
			if (proj->flipped_corner.find(k) != proj->flipped_corner.end()) {
				first = k;
			}
		}
		for (int i=first; i<=first+t->edges; i++) {
			proj->north_tile.push_back(&proj->corner[mesh::corner(t,i)->id]);
		}
		proj->north_tile.push_back(&proj->flipped_corner.find(mesh::corner(t,first)->id)->second);
		if (flip(*proj->north_tile[1], *proj->north_tile[2])) {
			proj->north_tile[1] = &proj->flipped_corner.find(mesh::corner(t,first)->id)->second;
		}
		else {
			proj->north_tile[proj->south_tile.size()-1] = &proj->flipped_corner.find(mesh::corner(t,first)->id)->second;
		}
		proj->north_tile.push_back(&proj->north_pole);
		proj->north_tile.push_back(proj->north_tile[1]);
		for (int i=proj->north_id*8+1; i<proj->north_id*8+8; i++) {
			proj->polygon[i] = proj->polygon[proj->north_id*8];
		}
	}
	
	if (proj->south_id >= 0) {
		const Tile* t = mesh::tile(p,proj->south_id);
		proj->south_tile.push_back(&proj->tile[proj->south_id]);
		int first = 0;
		for (int i=0; i<6; i++) {
			int k = mesh::corner(t,i)->id;
			if (proj->flipped_corner.find(k) != proj->flipped_corner.end()) {
				first = k;
			}
		}
		for (int i=first; i<=first+t->edges; i++) {
			proj->south_tile.push_back(&proj->corner[mesh::corner(t,i)->id]);
		}
		if (flip(*proj->south_tile[1], *proj->south_tile[2])) {
			proj->south_tile[1] = &proj->flipped_corner.find(mesh::corner(t,first)->id)->second;
		}
		else {
			proj->south_tile[proj->south_tile.size()-1] = &proj->flipped_corner.find(-mesh::corner(t,first)->id)->second;
		}
		proj->south_tile.push_back(&proj->south_pole);
		proj->south_tile.push_back(proj->south_tile[1]);
		for (int i=proj->south_id*8+1; i<proj->south_id*8+8; i++) {
			proj->polygon[i] = proj->polygon[proj->south_id*8];
		}
	}
}

bool flip (const Vector2& v, const Vector2& e) {
	return (v.x * e.x < 0);
}

Vector3 from_hammer (const Vector2& v) {
	double z = sqrt(1.0-pow(v.x/4.0,2.0)-pow(v.y/2.0,2.0));
	double latitude = asin(z*v.y);
	double longitude = 2.0*atan(z*v.x / (2.0*(2.0*z*z-1.0)));
	Vector3 vec = terrain::from_lat_long(latitude, longitude);
	return vec;
}

void init (const Planet* p, Projection* proj) {
	proj->p = p;
	create_geometry(proj);
}

Vector2 to_hammer (const Vector3& v) {
	double latitude = terrain::latitude(v);
	double longitude = terrain::longitude(v);
	Vector2 proj = Vector2();
	proj.x = 2.0*sqrt(2.0)*cos(latitude)*sin(longitude/2.0) / sqrt(1.0+cos(latitude)*cos(longitude/2.0));
	proj.y = sqrt(2.0)*sin(latitude) / sqrt(1.0+cos(latitude)*cos(longitude/2.0));
	return proj;
}
}
