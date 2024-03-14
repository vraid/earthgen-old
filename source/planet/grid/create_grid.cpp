#include "create_grid.h"
#include "grid.h"
#include <cmath>

namespace earthgen {

Grid size_n_grid (int size) {
	return (size <= 0) ? size_0_grid() : subdivide(size_n_grid(size - 1));
}

Grid size_0_grid () {
	Grid grid;
	grid.set_size(0);
	float x = -0.525731112119133606;
	float z = -0.850650808352039932;
	
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
		for (int k=0; k<5; k++) {
			t.tiles[k] = &grid.tiles[icos_tiles_n[t.id][k]];
		}
	}
	for (int i=0; i<5; i++) {
		add_corner(i, grid, 0, icos_tiles_n[0][(i+4)%5], icos_tiles_n[0][i]);
	}
	for (int i=0; i<5; i++) {
		add_corner(i+5, grid, 3, icos_tiles_n[3][(i+4)%5], icos_tiles_n[3][i]);
	}

	std::array<std::array<int, 3>, 10>
	remaining_adjacencies = {{
		{10,1,8}, {1,10,6}, {6,10,7}, {6,7,11}, {11,7,2}, {11,2,9}, {9,2,5}, {9,5,4}, {4,5,8}, {4,8,1}
	}};
	for (int i=0; i<10; i++) {
		auto adj = remaining_adjacencies[i];
		add_corner(i+10, grid, adj[0], adj[1], adj[2]);
	}
	
	//add corners to corners
	for (Corner& c : grid.corners) {
		for (int k=0; k<3; k++) {
			c.corners[k] = c.tiles[k]->corners[(position(c.tiles[k], &c)+1)%5];
		}
	}
	//new edges
	int next_edge_id = 0;
	for (Tile& t : grid.tiles) {
		for (int k=0; k<5; k++) {
			if (t.id < t.tiles[k]->id) {
				add_edge(next_edge_id, grid, t.id, icos_tiles_n[t.id][k]);
				next_edge_id++;
			}
		}
	}
	return grid;
}

Grid subdivide (const Grid& prev) {
	Grid grid;
	grid.set_size(prev.size + 1);

	int prev_tile_count = prev.tiles.size();
	int prev_corner_count = prev.corners.size();
	
	//old tiles
	for (int i=0; i<prev_tile_count; i++) {
		grid.tiles[i].v = prev.tiles[i].v;
		for (int k=0; k<grid.tiles[i].edge_count; k++) {
			grid.tiles[i].tiles[k] = &grid.tiles[prev.tiles[i].corners[k]->id+prev_tile_count];
		}
	}
	//old corners become tiles
	for (int i=0; i<prev_corner_count; i++) {
		grid.tiles[i+prev_tile_count].v = prev.corners[i].v;
		for (int k=0; k<3; k++) {
			grid.tiles[i+prev_tile_count].tiles[2*k] = &grid.tiles[prev.corners[i].corners[k]->id+prev_tile_count];
			grid.tiles[i+prev_tile_count].tiles[2*k+1] = &grid.tiles[prev.corners[i].tiles[k]->id];
		}
	}
	//new corners
	int next_corner_id = 0;
	for (const Tile& n : prev.tiles) {
		const Tile& t = grid.tiles[n.id];
		for (int k=0; k<t.edge_count; k++) {
			add_corner(next_corner_id, grid, t.id, t.tiles[(k+t.edge_count-1)%t.edge_count]->id, t.tiles[k]->id);
			next_corner_id++;
		}
	}
	//connect corners
	for (Corner& c : grid.corners) {
		for (int k=0; k<3; k++) {
			c.corners[k] = c.tiles[k]->corners[(position(c.tiles[k], &c)+1)%(c.tiles[k]->edge_count)];
		}
	}
	//new edges
	int next_edge_id = 0;
	for (Tile& t : grid.tiles) {
		for (int k=0; k<t.edge_count; k++) {
			if (t.id < t.tiles[k]->id) {
				add_edge(next_edge_id, grid, t.id, t.tiles[k]->id);
				next_edge_id++;
			}
		}
	}
	return grid;
}

void add_corner (int id, Grid& grid, int t1, int t2, int t3) {
	Corner *c = &grid.corners[id];
	Tile *t[3] = {&grid.tiles[t1], &grid.tiles[t2], &grid.tiles[t3]};
	Vector3 v = t[0]->v + t[1]->v + t[2]->v;
	c->v = normal(v);
	for (int i=0; i<3; i++) {
		t[i]->corners[position(t[i], t[(i+2)%3])] = c;
		c->tiles[i] = t[i];
	}
}
void add_edge (int id, Grid& grid, int t1, int t2) {
	Edge *e = &grid.edges[id];
	Tile *t[2] = {&grid.tiles[t1], &grid.tiles[t2]};
	Corner *c[2] = {
		&grid.corners[t[0]->corners[position(t[0], t[1])]->id],
		&grid.corners[t[0]->corners[(position(t[0], t[1])+1)%t[0]->edge_count]->id]};
	for (int i=0; i<2; i++) {
		t[i]->edges[position(t[i], t[(i+1)%2])] = e;
		e->tiles[i] = t[i];
		c[i]->edges[position(c[i], c[(i+1)%2])] = e;
		e->corners[i] = c[i];
	}
}

}
