#include <math.h>
#include "grid.h"

Grid::Grid (int s) :
	size (s) {
	for (int i=0; i<tile_count(size); i++)
		tiles.push_back(Tile(i, i<12 ? 5 : 6));
	for (int i=0; i<corner_count(size); i++)
		corners.push_back(Corner(i));
	for (int i=0; i<edge_count(size); i++)
		edges.push_back(Edge(i));
}

int tile_count (int size) {return 10*pow(3,size)+2;}
int corner_count (int size) {return 20*pow(3,size);}
int edge_count (int size) {return 30*pow(3,size);}
