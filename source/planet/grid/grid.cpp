#include "grid.h"
#include "../planet.h"

Grid::Grid (int s) :
	size (s) {
	for (int i=0; i<tile_count(size); i++)
		tiles.push_back(Tile(i, i<12 ? 5 : 6));
	for (int i=0; i<corner_count(size); i++)
		corners.push_back(Corner(i));
	for (int i=0; i<edge_count(size); i++)
		edges.push_back(Edge(i));
}

void set_grid_size (Planet& p, int size) {
	delete p.grid;
	p.grid = size_n_grid(size);
}

const std::deque<Tile>& tiles (const Planet& p) {return p.grid->tiles;}
const std::deque<Corner>& corners (const Planet& p) {return p.grid->corners;}
const std::deque<Edge>& edges (const Planet& p) {return p.grid->edges;}

const Tile* nth_tile (const Planet& p, int n) {return &p.grid->tiles[n];}
const Corner* nth_corner (const Planet& p, int n) {return &p.grid->corners[n];}
const Edge* nth_edge (const Planet& p, int n) {return &p.grid->edges[n];}

int tile_count (const Planet& p) {return p.grid->tiles.size();}
int corner_count (const Planet& p) {return p.grid->corners.size();}
int edge_count (const Planet& p) {return p.grid->edges.size();}

int tile_count (int size) {return 10*pow(3,size)+2;}
int corner_count (int size) {return 20*pow(3,size);}
int edge_count (int size) {return 30*pow(3,size);}