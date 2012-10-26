#ifndef create_grid_h
#define create_grid_h

#define nullptr NULL

class Grid;

namespace grid {
	void add_corner (int, Grid*, int, int, int);
	void add_edge (int, Grid*, int, int);
	Grid* create (int);
	Grid* icosahedron ();
	Grid* subdivision (const Grid*);
	int validate (const Grid*);
}

#endif
