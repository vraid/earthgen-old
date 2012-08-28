#include "terrain.h"
#include "../planet.h"
#include "../../math/vector3.h"
#include "../../noise/noise.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <map>

namespace terrain {

void classify_corners (Planet* p) {
	const Corner* corner = mesh::corner(p,0);
	Terrain_corner* corner_ter = terrain::corner(p,0);
	for (int i=0; i<mesh::corners(p); i++) {
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
	const Edge* edge = mesh::edge(p,0);
	Terrain_edge* edge_ter = terrain::edge(p,0);
	for (int i=0; i<mesh::edges(p); i++) {
		if (tile(p,edge[i].tile[0])->is_land + tile(p,edge[i].tile[1])->is_land == 1) {
			edge_ter[i].is_coast = true;
		}
		else edge_ter[i].is_coast = false;
	}
}

void classify_tiles (Planet* p) {
	const Tile* tile = mesh::tile(p,0);
	Terrain_tile* tile_ter = terrain::tile(p,0);
	for (int i=0; i<mesh::tiles(p); i++) {
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

Terrain_corner* corner (Planet* p, int i) {
	return &p->terrain->corner[i];
}

Terrain_corner* corner (Planet* p, const Corner* c) {
	return &p->terrain->corner[c->id];
}

Terrain_edge* edge (Planet* p, int i) {
	return &p->terrain->edge[i];
}

Terrain_edge* edge (Planet* p, const Edge* e) {
	return &p->terrain->edge[e->id];
}

vector<Terrain_edge>& edge_vector (Planet* p) {
	return p->terrain->edge;
}

double elevation (const Planet* p, const Vector3& v) {
	return p->par.elevation_scale * noise::noise(p->par.terrain_noise, v);
}

double find_sea_level (Planet* p) {
	double ratio = p->par.water_ratio;
	double sea_level = 0.0;
	if (ratio <= 0.0) sea_level = -p->par.elevation_scale;
	else if (ratio >= 1.0) sea_level = p->par.elevation_scale;
	else {
		vector<double> v;
		v.reserve(mesh::tiles(p));
		for (int i=0; i<mesh::tiles(p); i++) {
			v.push_back(tile(p,i)->elevation);
		}
		sort(v.begin(), v.end());
		sea_level = v[ratio*mesh::tiles(p)]+0.01;
	}
	return sea_level;
}

Vector3 from_lat_long (double lat, double lon) {
	return Vector3(cos(lon), sin(lon), sin(lat));
}

void generate (Planet* p) {
	set_elevation(p);
	set_sea_level(p);
	set_stream_directions(p);
}

void init (Planet* p) {
	Terrain* t = p->terrain;
	t->tile.resize(mesh::tiles(p));
	t->corner.resize(mesh::corners(p));
	t->edge.resize(mesh::edges(p));
}

double latitude (const Vector3& v) {
	return asin(v.z);
}

double longitude (const Vector3& v) {
	return atan2(v.y, v.x);
}

void reset_stream_directions (Planet* p) {
	for (int i=0; i<mesh::corners(p); i++) {
		corner(p,i)->stream_direction = nullptr;
	}
}

void set_elevation (Planet* p) {
	const Tile* tile = mesh::tile(p,0);
	Terrain_tile* tile_ter = terrain::tile(p,0);
	for (int i=0; i<mesh::tiles(p); i++) {
		tile_ter[i].elevation = elevation(p, tile[i].v);
	}
	const Corner* corner = mesh::corner(p,0);
	Terrain_corner* corner_ter = terrain::corner(p,0);
	for (int i=0; i<mesh::corners(p); i++) {
		corner_ter[i].elevation = elevation(p, corner[i].v);
	}
	p->terrain->var.highest_point = p->par.elevation_scale;
	p->terrain->var.lowest_point = -p->par.elevation_scale;
}

void set_sea_level (Planet* p) {
	double sea_level = find_sea_level(p);
	p->terrain->var.sea_level = sea_level;
	std::cout << "sea level = " << sea_level << std::endl;
	Terrain_tile* tile = terrain::tile(p,0);
	for (int i=0; i<mesh::tiles(p); i++) {
		if (tile[i].elevation < sea_level) {
			tile[i].water.depth = sea_level - tile[i].elevation;
			tile[i].water.level = sea_level;
		}
		else {
			tile[i].water.depth = 0;
		}
	}
	std::cout << "classify..";
	std::cout << " tiles";
	classify_tiles(p);
	std::cout << ", corners";
	classify_corners(p);
	std::cout << ", edges";
	classify_edges(p);
	std::cout << ". done\n";
}

void set_stream_directions (Planet* p) {
	reset_stream_directions(p);
	std::multimap<float,int> flood;
	for (int i=0; i<mesh::corners(p); i++) {
		if (corner(p,i)->is_coast) flood.insert(std::pair<float,int>(corner(p,i)->elevation, i));
	}
	while (flood.size() > 0) {
		const Corner* c = mesh::corner(p,flood.begin()->second);
		flood.erase(flood.begin());
		for (int i=0; i<3; i++) {
			Terrain_corner* k = corner(p,mesh::corner(c,i)->id);
			if (k->is_land && k->stream_direction == nullptr) {
				k->stream_direction = c;
				flood.insert(std::pair<float,int>(k->elevation, mesh::corner(c,i)->id));
			}
		}
	}
}

Terrain_tile* tile (Planet* p, int i) {
	return &p->terrain->tile[i];
}

Terrain_tile* tile (Planet* p, const Tile* t) {
	return &p->terrain->tile[t->id];
}

vector<Terrain_tile>& tile_vector (Planet* p) {
	return p->terrain->tile;
}

}
