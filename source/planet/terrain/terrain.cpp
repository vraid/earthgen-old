#include "terrain.h"
#include "../planet.h"
#include "../../math/vector3.h"
#include "../../noise/noise.h"
#include "../../hash/md5.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <ctime>

namespace terrain {

void generate (Planet* p) {
	init(p);
	std::cout << "generating terrain\n";
	set_elevation(p);
	set_sea_level(p);
	set_water_bodies(p);
	set_river_directions(p);
	grid::rotate(p->grid, p->par.rotation);
}

void init (Planet* p) {
	Terrain* t = p->terrain;
	t->tile.resize(grid::tiles(p));
	t->corner.resize(grid::corners(p));
	t->edge.resize(grid::edges(p));
	p->terrain->var.axial_tilt = p->par.axial_tilt;
}

void classify_corners (Planet* p) {
	const Corner* corner = grid::corner(p,0);
	Terrain_corner* corner_ter = m_corner(p,0);
	for (int i=0; i<grid::corners(p); i++) {
		int land = 0;
		int water = 0;
		for (int k=0; k<3; k++) {
			if (tile(p, corner[i].tile[k])->is_land) land++;
			else water++;
		}
		corner_ter[i].is_land = false;
		corner_ter[i].is_water = false;
		if (!water) corner_ter[i].is_land = true;
		if (!land) corner_ter[i].is_water = true;
		if (land && water) corner_ter[i].is_coast = true;
		else corner_ter[i].is_coast = false;
	}
}

void classify_edges (Planet* p) {
	const Edge* edge = grid::edge(p,0);
	Terrain_edge* edge_ter = m_edge(p,0);
	for (int i=0; i<grid::edges(p); i++) {
		if (tile(p,edge[i].tile[0])->is_land + tile(p,edge[i].tile[1])->is_land == 1) {
			edge_ter[i].is_coast = true;
		}
		else edge_ter[i].is_coast = false;
	}
}

void classify_tiles (Planet* p) {
	const Tile* tile = grid::tile(p,0);
	Terrain_tile* tile_ter = m_tile(p,0);
	for (int i=0; i<grid::tiles(p); i++) {
		if (tile_ter[i].water.depth == 0) tile_ter[i].is_land = true;
		else tile_ter[i].is_land = false;
		tile_ter[i].is_water = !tile_ter[i].is_land;
		tile_ter[i].has_coast = false;
		for (int k=0; k<tile[i].edges; k++) {
			if (tile_ter[i].is_land && terrain::tile(p,tile[i].tile[k])->water.depth > 0) tile_ter[i].has_coast = true;
			if (tile_ter[i].is_water && terrain::tile(p,tile[i].tile[k])->water.depth == 0) tile_ter[i].has_coast = true;
		}
	}
}

double point_elevation (Vector3 v, const std::vector<Vector3>& point, int iterations) {
	double elevation = 0;
	for (int i=0; i<iterations; i++) {
		if (vector3::distance_square(v,point[2*i]) < 2.0 && vector3::distance_square(v,point[2*i+1]) < 2.0) {
			elevation++;
		}
	}
	return elevation;
}

void scale_elevation (Planet* p) {
	double lowest = p->par.iterations;
	double highest = 0;
	for (int i=0; i<grid::tiles(p); i++) {
		double e = terrain::tile(p,i)->elevation;
		if (lowest > e) lowest = e;
		if (highest < e) highest = e;
	}
	for (int i=0; i<grid::corners(p); i++) {
		double e = terrain::corner(p,i)->elevation;
		if (lowest > e) lowest = e;
		if (highest < e) highest = e;
	}

	//prevent division by zero
	if (highest == lowest) highest++;

	for (int i=0; i<grid::tiles(p); i++) {
		double e = terrain::tile(p,i)->elevation;
		terrain::m_tile(p,i)->elevation = 2*p->par.elevation_scale * (e-lowest)/(highest-lowest) - p->par.elevation_scale;
	}
	for (int i=0; i<grid::corners(p); i++) {
		double e = terrain::corner(p,i)->elevation;
		terrain::m_corner(p,i)->elevation = 2*p->par.elevation_scale * (e-lowest)/(highest-lowest) - p->par.elevation_scale;
	}
}

void smoothe_elevation (Planet* p) {
	std::vector<double> tiles;
	tiles.resize(grid::tiles(p));
	std::vector<double> corners;
	corners.resize(grid::corners(p));

	for (int i=0; i<grid::tiles(p); i++) {
		double e = terrain::tile(p,i)->elevation;
		for (int k=0; k<grid::tile(p,i)->edges; k++) {
			e += terrain::tile(p,grid::tile(grid::tile(p,i),k))->elevation / grid::tile(p,i)->edges;
		}
		e /= 2.0;
		tiles[i] = e;
	}

	for (int i=0; i<grid::corners(p); i++) {
		double e = terrain::corner(p,i)->elevation;
		for (int k=0; k<3; k++) {
			e += terrain::corner(p,grid::corner(grid::corner(p,i),k))->elevation / 3.0;
		}
		e /= 2.0;
		corners[i] = e;
	}

	for (int i=0; i<grid::tiles(p); i++) {
		terrain::m_tile(p,i)->elevation = tiles[i];
	}
	for (int i=0; i<grid::corners(p); i++) {
		terrain::m_corner(p,i)->elevation = corners[i];
	}
}

void set_elevation (Planet* p) {
	std::vector<Vector3> point;
	point.resize(2*p->par.iterations);

	std::string md = md5(p->par.terrain_seed);
	unsigned long hash = 0;
	for (unsigned int i=0; i<md.length(); i++) {
		hash *= 16;
		hash += md[i];
		if (md[i] >= 'a') hash += 10 - 'a';
		else hash -= '0';
	}
	
	std::cout << "seed = " << p->par.terrain_seed << std::endl;
	std::cout << "iterations = " << p->par.iterations << std::endl;
	
	srand(hash);
	for (int i=0; i<p->par.iterations; i++) {
		for (int k=0; k<2; k++) {
			double x = 2*pi*(rand()/(double)RAND_MAX);
			double y = acos(2*(rand()/(double)RAND_MAX)-1)-(0.5*pi);
			point[2*i+k] = Vector3(sin(x)*cos(y), sin(y), cos(x)*cos(y));
		}
	}
	
	for (int i=0; i<grid::tiles(p); i++) {
		terrain::m_tile(p,i)->elevation = point_elevation(grid::tile(p,i)->v, point, p->par.iterations);
	}
	for (int i=0; i<grid::corners(p); i++) {
		terrain::m_corner(p,i)->elevation = point_elevation(grid::corner(p,i)->v, point, p->par.iterations);
	}
	smoothe_elevation(p);
	scale_elevation(p);
}

void set_sea_level (Planet* p) {
	double sea_level = find_sea_level(p);
	p->terrain->var.sea_level = sea_level;
	std::cout << "sea level = " << sea_level << std::endl;
	Terrain_tile* tile = m_tile(p,0);
	for (int i=0; i<grid::tiles(p); i++) {
		if (tile[i].elevation < sea_level) {
			tile[i].water.depth = sea_level - tile[i].elevation;
			tile[i].water.level = sea_level;
		}
		else {
			tile[i].water.depth = 0;
		}
	}
	classify_tiles(p);
	classify_corners(p);
	classify_edges(p);
}

void create_water_body (Planet* p, int tile) {
	int id = p->terrain->water_bodies.size();
	p->terrain->water_bodies.push_back(Water_body());
	Water_body* body = &p->terrain->water_bodies.back();
	body->id = id;

	const Tile* t = grid::tile(p,tile);
	terrain::m_tile(p,tile)->water.body = id;
	body->tile.insert(t);
	std::set<const Tile*> search;
	search.insert(t);
	while (!search.empty()) {
		t = *search.begin();
		search.erase(t);
		for (int k=0; k<t->edges; k++) {
			const Tile* n = grid::tile(t,k);
			if (terrain::tile(p,n)->is_water && terrain::tile(p,n)->water.body == -1) {
				terrain::m_tile(p,n->id)->water.body = id;
				body->tile.insert(n);
				search.insert(n);
			}
		}
	}
}

void set_water_bodies (Planet* p) {
	p->terrain->water_bodies.clear();
	for (int i=0; i<grid::tiles(p); i++) {
		if (terrain::tile(p,i)->is_water == true) {
			terrain::m_tile(p,i)->water.body = -1;
		}
	}
	
	for (int i=0; i<grid::tiles(p); i++) {
		if (terrain::tile(p,i)->is_water == true && terrain::tile(p,i)->water.body == -1) {
			create_water_body(p,i);
		}
	}
}

void set_basins (Planet* p) {
	std::multimap<int,Water_body*> bodies;
	for (unsigned int i=0; i<p->terrain->water_bodies.size(); i++) {
		bodies.insert(std::pair<int,Water_body*>(p->terrain->water_bodies[i].tile.size(), &p->terrain->water_bodies[i]));
	}
	double basin_depth = 500.0;
	//start with largest basin, include all up to basin depth and mark all but starting point as non-basins
	//repeat for each body not yet marked
	//set river directions, starting from basins
}

void reset_river_directions (Planet* p) {
	for (int i=0; i<grid::corners(p); i++) {
		m_corner(p,i)->river_direction = nullptr;
		m_corner(p,i)->sea_distance = 0;
	}
}

void set_river_directions (Planet* p) {
	reset_river_directions(p);
	std::multimap<float,int> flood;
	for (int i=0; i<grid::corners(p); i++) {
		if (corner(p,i)->is_coast) flood.insert(std::pair<float,int>(corner(p,i)->elevation, i));
	}
	while (flood.size() > 0) {
		const Corner* c = grid::corner(p,flood.begin()->second);
		flood.erase(flood.begin());
		for (int i=0; i<3; i++) {
			Terrain_corner* k = m_corner(p,grid::corner(c,i)->id);
			if (k->is_land && k->river_direction == nullptr) {
				k->river_direction = c;
				k->sea_distance = corner(p,c)->sea_distance + 1;
				flood.insert(std::pair<float,int>(k->elevation, grid::corner(c,i)->id));
			}
		}
	}
}

double find_sea_level (Planet* p) {
	double ratio = p->par.water_ratio;
	double sea_level = 0.0;
	if (ratio <= 0.0) sea_level = -p->par.elevation_scale;
	else if (ratio >= 1.0) sea_level = p->par.elevation_scale;
	else {
		vector<double> v;
		v.reserve(grid::tiles(p));
		for (int i=0; i<grid::tiles(p); i++) {
			v.push_back(tile(p,i)->elevation);
		}
		sort(v.begin(), v.end());
		sea_level = v[ratio*grid::tiles(p)]+0.01;
	}
	return sea_level;
}

Vector3 from_lat_long (double lat, double lon) {
	return Vector3(cos(lon)*cos(lat), sin(lon)*cos(lat), sin(lat));
}

double latitude (const Vector3& v) {
	return asin(v.z);
}

double longitude (const Vector3& v) {
	return atan2(v.y, v.x);
}

double north (const Planet* p, const Tile* t) {
	Vector3 v = grid::reference_rotation(t)*grid::tile(t,0)->v;
	return -atan2(v.y, v.x);
}

double circumference (const Planet* p) {
	return p->terrain->var.radius * 2.0 * pi;
}


const Terrain_tile* tile (const Planet* p, int id) {
	return &p->terrain->tile[id];
}
const Terrain_tile* tile (const Planet* p, const Tile* t) {
	return &p->terrain->tile[t->id];
}
const Terrain_corner* corner (const Planet* p, int id) {
	return &p->terrain->corner[id];
}
const Terrain_corner* corner (const Planet* p, const Corner* c) {
	return &p->terrain->corner[c->id];
}
const Terrain_edge* edge (const Planet* p, int id) {
	return &p->terrain->edge[id];
}
const Terrain_edge* edge (const Planet* p, const Edge* e) {
	return &p->terrain->edge[e->id];
}
Terrain_tile* m_tile (Planet* p, int id) {
	return &p->terrain->tile[id];
}
Terrain_corner* m_corner (Planet* p, int id) {
	return &p->terrain->corner[id];
}
Terrain_edge* m_edge (Planet* p, int id) {
	return &p->terrain->edge[id];
}

} 
