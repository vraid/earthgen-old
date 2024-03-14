#ifndef create_grid_h
#define create_grid_h

class Grid;

Grid size_n_grid (int);
Grid size_0_grid ();
Grid subdivide (const Grid&);

void add_corner (int, Grid&, int, int, int);
void add_edge (int, Grid&, int, int);

#endif
