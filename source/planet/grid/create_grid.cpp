#include "create_grid.h"
#include "grid.h"
#include <cmath>
#include <array>

namespace earthgen {

void add_corner (Grid& grid, std::array<int, 3> ids) {
	int id = grid.corners.size();
	grid.corners.push_back(Corner(id));
	Corner *c = &grid.corners[id];
	auto& tiles = grid.tiles;
	std::array<Tile*, 3> t = {&tiles[ids[0]], &tiles[ids[1]], &tiles[ids[2]]};
	Vector3 v = t[0]->v + t[1]->v + t[2]->v;
	c->v = normal(v);
	for (int i : corner_indices()) {
		t[i]->corners[position(t[i], t[(i+2)%3])] = c;
		c->tiles[i] = t[i];
	}
}

void add_edge (Grid& grid, std::array<int, 2> ids) {
	int id = grid.edges.size();
	grid.edges.push_back(Edge(id));
	Edge *e = &grid.edges[id];
	auto& tiles = grid.tiles;
	std::array<Tile*, 2> t = {&tiles[ids[0]], &tiles[ids[1]]};
	auto pos = position(t[0], t[1]);
	Corner *c[2] = {
		&grid.corners[t[0]->corners[pos]->id],
		&grid.corners[t[0]->corners[(pos+1)%edge_count(t[0])]->id]};
	for (int i : edge_indices()) {
		t[i]->edges[position(t[i], t[(i+1)%2])] = e;
		e->tiles[i] = t[i];
		c[i]->edges[position(c[i], c[(i+1)%2])] = e;
		e->corners[i] = c[i];
	}
}

void add_corners (Grid& grid) {
	for (const Tile& t : grid.tiles) {
		for (int k : indices(t)) {
			int id = t.id;
			int t1 = t.tiles[(k+edge_count(t)-1)%edge_count(t)]->id;
			int t2 = t.tiles[k]->id;
			if (id < t1 && id < t2) {
				add_corner(grid, std::array<int, 3>({id, t1, t2}));
			}
		}
	}
}

void connect_corners (Grid& grid) {
	for (Corner& c : grid.corners) {
		for (int k : corner_indices()) {
			auto t = c.tiles[k];
			c.corners[k] = t->corners[(position(t, &c)+1)%edge_count(*t)];
		}
	}
}

void add_edges (Grid& grid) {
	for (Tile& t : grid.tiles) {
		for (int k : indices(t)) {
			int id = t.id;
			int n = t.tiles[k]->id;
			if (id < n) {
				add_edge(grid, std::array<int, 2>({id, n}));
			}
		}
	}
}

void add_tiles (Grid& grid, const Grid& prev) {
	int prev_tile_count = prev.tiles.size();
	int prev_corner_count = prev.corners.size();

	auto& tiles = grid.tiles;

	for (int i=0; i<prev_tile_count; i++) {
		tiles[i].v = prev.tiles[i].v;
		for (int k : indices(tiles[i])) {
			tiles[i].tiles[k] = &tiles[prev.tiles[i].corners[k]->id+prev_tile_count];
		}
	}
	for (int i=0; i<prev_corner_count; i++) {
		auto& tile = tiles[i+prev_tile_count];
		tile.v = prev.corners[i].v;
		for (int k : corner_indices()) {
			tile.tiles[2*k] = &tiles[prev.corners[i].corners[k]->id+prev_tile_count];
			tile.tiles[2*k+1] = &tiles[prev.corners[i].tiles[k]->id];
		}
	}
}

void add_icos_tiles (Grid& grid) {
	double x = -0.525731112119133606;
	double z = -0.850650808352039932;

	std::array<Vector3, 12>
	icos_tiles = {
		Vector3(-x, 0, z),
		Vector3(x, 0, z),
		Vector3(-x, 0, -z),
		Vector3(x, 0, -z),
		Vector3(0, z, x),
		Vector3(0, z, -x),
		Vector3(0, -z, x),
		Vector3(0, -z, -x),
		Vector3(z, x, 0),
		Vector3(-z, x, 0),
		Vector3(z, -x, 0),
		Vector3(-z, -x, 0)
	};

	std::array<std::array<int, 5>, 12>
	icos_tiles_n = {{
		{9, 4, 1, 6, 11},
		{4, 8, 10, 6, 0},
		{11, 7, 3, 5, 9},
		{2, 7, 10, 8, 5},
		{9, 5, 8, 1, 0},
		{2, 3, 8, 4, 9},
		{0, 1, 10, 7, 11},
		{11, 6, 10, 3, 2},
		{5, 3, 10, 1, 4},
		{2, 5, 4, 0, 11},
		{3, 7, 6, 1, 8},
		{7, 2, 9, 0, 6}
	}};

	for (Tile& t : grid.tiles) {
		t.v = icos_tiles[t.id];
		for (int k : indices(t)) {
			t.tiles[k] = &grid.tiles[icos_tiles_n[t.id][k]];
		}
	}
}

double tile_area (const Tile& t) {
	std::array<Vector3, 6> normals;
	std::array<double, 6> lengths;
	auto& vec = vector(t);
	for (int n : indices(t)) {
		Vector3 diff = vec - vector(nth_corner(t,n));
		normals[n] = normal(diff);
		lengths[n] = length(diff);
	}
	double accum = 0.0;
	for (int k : indices(t)) {
		int n = (k+1) % edge_count(t);
		double angle = std::acos(dot_product(normals[k], normals[n]));
		accum += std::sin(angle) * lengths[k] * lengths[n];
	}
	return accum * 0.5;
}

void set_tile_areas (Grid& grid) {
	for (Tile& t : grid.tiles) {
		t.area = tile_area(t);
	}
}

void complete_grid (Grid& grid) {
	add_corners(grid);
	connect_corners(grid);
	add_edges(grid);
	set_tile_areas(grid);
}

void size_0_grid (Grid& grid) {
	grid.set_size(0);

	add_icos_tiles(grid);
	complete_grid(grid);
}

void subdivide (Grid& grid, const Grid& prev) {
	grid.set_size(prev.size + 1);

	add_tiles(grid, prev);
	complete_grid(grid);
}

}
