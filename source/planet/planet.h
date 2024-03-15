#ifndef planet_h
#define planet_h

#include "grid/grid.h"
#include "terrain/terrain.h"
#include "climate/climate.h"

namespace earthgen {

class Planet {
public:
	Planet ();
	
	Grid grid;
	Terrain terrain;
	Climate climate;
};

void clear (Planet&);
void set_grid_size (Planet&, int);

}

#endif
