#include "terrain_generation.h"
#include "../planet.h"
#include <cmath>
#include <cstdlib>
#include <map>
#include <set>
#include <utility>
#include "../../math/math_common.h"
#include "../../hash/md5.h"

#include <iostream>
void generate_terrain (Planet& p, const Terrain_parameters& par) {
	clear(p);
	set_grid_size(p, par.grid_size);
	init_terrain(p);
	_set_variables(p, par);
	_set_elevation(p, par);
	_create_sea(p, par);
	_classify_terrain(p);
	_set_river_directions(p);
}

void _set_variables (Planet& p, const Terrain_parameters& par) {
	p.terrain.var.axis = par.axis;
	p.terrain.var.radius = 40000000;
}

void _set_elevation (Planet& p, const Terrain_parameters& par) {
	// can be made concurrent
	auto d = _elevation_vectors(par);
	for (auto& t : tiles(p))
		m_terrain_tile(p, t.id).elevation = _elevation_at_point(t.v, d);
	for (auto& c : corners(p))
		m_terrain_corner(p, c.id).elevation = _elevation_at_point(c.v, d);
	_scale_elevation(p, par);
}

void _scale_elevation (Planet& p, const Terrain_parameters&) {
	float lowest = nth_terrain_tile(p,0).elevation;
	float highest = lowest;
	float scale = 3000;
	for (auto& t : terrain_tiles(p)) {
		lowest = std::min(lowest, t.elevation);
		highest = std::max(highest, t.elevation);
	}
	for (auto& c : terrain_corners(p)) {
		lowest = std::min(lowest, c.elevation);
		highest = std::max(highest, c.elevation);
	}
	highest = std::max(1.0f, highest-lowest);
	for (auto& t : tiles(p)) {
		m_terrain_tile(p, t.id).elevation -= lowest;
		m_terrain_tile(p, t.id).elevation *= scale / highest;
	}
	for (auto& c : corners(p)) {
		m_terrain_corner(p, c.id).elevation -= lowest;
		m_terrain_corner(p, c.id).elevation *= scale / highest;
	}
}

const Tile* lowest_tile (const Planet& p) {
	const Tile* tile = nth_tile(p, 0);
	float lowest_elevation = nth_terrain_tile(p, 0).elevation;
	for (const Tile& t : tiles(p)) {
		if (nth_terrain_tile(p, t.id).elevation < lowest_elevation) {
			tile = &t;
			lowest_elevation = nth_terrain_tile(p, t.id).elevation;
		}
	}
	return tile;
}

void _create_sea (Planet& p, const Terrain_parameters& par) {
	const Tile* const start_tile = lowest_tile(p);
	float sea_level = nth_terrain_tile(p, id(start_tile)).elevation;
	unsigned int water_tile_count = par.water_ratio * tile_count(p);
	std::set<const Tile*> water_tiles;
	std::multimap<float, const Tile*> coast_tiles_elevation;
	std::vector<bool> coast_tiles;
	if (water_tile_count > 0) {
		water_tiles.insert(start_tile);
		coast_tiles.resize(tile_count(p), false);
		for (const Tile* i : tiles(start_tile)) {
			coast_tiles[id(i)] = true;
			coast_tiles_elevation.insert(std::make_pair(nth_terrain_tile(p,id(i)).elevation, i));
		}
		const Tile* tile;
		auto insert_next_tile = [&]() {
			tile = coast_tiles_elevation.begin()->second;
			water_tiles.insert(tile);
			coast_tiles[id(tile)] = false;
			coast_tiles_elevation.erase(coast_tiles_elevation.begin());
			for (auto i : tiles(tile)) {
				if (water_tiles.find(i) == water_tiles.end() && !coast_tiles[id(i)]) {
					coast_tiles[id(i)] = true;
					coast_tiles_elevation.insert(std::make_pair(nth_terrain_tile(p,id(i)).elevation, i));
				}
			}
		};
		while (water_tiles.size() < water_tile_count) {
			insert_next_tile();
			sea_level = nth_terrain_tile(p, id(tile)).elevation;
			while (coast_tiles_elevation.size() > 0 && coast_tiles_elevation.begin()->first <= sea_level) {
				insert_next_tile();
			}
		}
		if (coast_tiles_elevation.size() > 0)
			sea_level = (sea_level + coast_tiles_elevation.begin()->first) / 2;
	}
	p.terrain.var.sea_level = sea_level;
	for (auto t : water_tiles) {
		m_terrain_tile(p, t->id).water.surface = sea_level;
		m_terrain_tile(p, t->id).water.depth = sea_level - nth_terrain_tile(p, t->id).elevation;
	}
}

int _tile_type (const Planet& p, const Tile* t) {
	int land = 0;
	int water = 0;
	for (auto i : tiles(t)) {
		if (water_depth(nth_terrain_tile(p,id(i))) > 0) water++;
		else land++;
	}
	int type =
		water_depth(nth_terrain_tile(p,id(t))) > 0 ?
			Terrain_tile::type_water :
			Terrain_tile::type_land;
	if (land && water)
		type += Terrain_tile::type_coast;
	return type;
}
		
int _corner_type (const Planet& p, const Corner* c) {
	int land = 0;
	int water = 0;
	for (auto i : tiles(c)) {
		if (water_depth(nth_terrain_tile(p,id(i))) > 0) water++;
		else land++;
	}
	int type =
		land && water ?
			Terrain_corner::type_coast :
			land ?
				Terrain_corner::type_land :
				Terrain_corner::type_water;
	return type;
}

int _edge_type (const Planet& p, const Edge* e) {
	int land = 0;
	int water = 0;
	for (auto i : tiles(e)) {
		if (water_depth(nth_terrain_tile(p,id(i))) > 0) water++;
			else land++;
	}
	int type =
		land && water ?
			Terrain_edge::type_coast :
			land ?
				Terrain_edge::type_land :
				Terrain_edge::type_water;
	return type;
}

void _classify_terrain (Planet& p) {
	for (auto& t : tiles(p))
		m_terrain_tile(p, t.id).type = _tile_type(p, &t);
	for (auto& c : corners(p))
		m_terrain_corner(p, c.id).type = _corner_type(p, &c);
	for (auto& e : edges(p))
		m_terrain_edge(p, e.id).type = _edge_type(p, &e);
}

void _set_river_directions (Planet& p) {
	std::multimap<float, const Corner*> endpoints;
	for (auto& c : corners(p))
		if (is_coast(nth_terrain_corner(p, c.id))) {
			m_terrain_corner(p, c.id).distance_to_sea = 0;
			endpoints.insert(std::make_pair(nth_terrain_corner(p, c.id).elevation, &c));
		}
	while (endpoints.size() > 0) {
		auto first = endpoints.begin();
		const Corner* c = first->second;
		for (auto n : corners(c)) {
			Terrain_corner& ter = m_terrain_corner(p, id(n));
			if (is_land(ter) && ter.river_direction == -1) {
				ter.river_direction = position(n, c);
				ter.distance_to_sea = 1 + nth_terrain_corner(p, id(c)).distance_to_sea;
				endpoints.insert(std::make_pair(ter.elevation, n));
			}
		}
		endpoints.erase(first);			
	}
}

unsigned int hex_string_to_uint (std::string s) {
	unsigned int n = 0;
	for (unsigned int i=0; i<s.length(); i++) {
		n *= 16;
		n += s[i];
		if (s[i] >= 'a') n += 10 - 'a';
		else if (s[i] >= 'A') n += 10 - 'A';
		else n -= '0';
	}
	return n;
}

std::vector<std::array<Vector3, 3> > _elevation_vectors (const Terrain_parameters& par) {
	srand(hex_string_to_uint(md5(par.seed)));
	std::vector<std::array<Vector3, 3> > d;
	for (int i=0; i<par.iterations; i++) {
		std::array<Vector3, 3> v = {{
			point_uniform(rand(), rand()),
			point_uniform(rand(), rand()),
			point_uniform(rand(), rand())}};
		d.push_back(v);
	}
	return d;
}

float _elevation_at_point (const Vector3& point, const std::vector<std::array<Vector3, 3> >& elevation_vectors) {
	float elevation = 0;
	for (auto& i : elevation_vectors) {
		if (
			squared_distance(point, i[0]) < 2.0 &&
			squared_distance(point, i[1]) < 2.0 &&
			squared_distance(point, i[2]) < 2.0) {
			elevation++;
		}
	}
	return elevation;
}

Vector3 point_uniform (int a, int b) {
	double x = 2*pi*(a/(double)RAND_MAX);
	double y = acos(2*(b/(double)RAND_MAX)-1)-(0.5*pi);
	return Vector3(sin(x)*cos(y), sin(y), cos(x)*cos(y));
}