#ifndef create_grid_h
#define create_grid_h

class Grid;

Grid* size_n_grid (int);
Grid* size_0_grid ();
Grid* _subdivided_grid (Grid*);

void _add_corner (int, Grid*, int, int, int);
void _add_edge (int, Grid*, int, int);

#endif