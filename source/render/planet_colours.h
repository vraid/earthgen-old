#ifndef planet_colours_h
#define planet_colours_h

#include <vector>
#include "colour.h"

namespace earthgen {

class Grid;
class Terrain;
class Season;
class Climate;

class Planet_colours {
public:
	Planet_colours () {}

	std::vector<Colour> tiles;

	enum {TOPOGRAPHY, VEGETATION, TEMPERATURE, ARIDITY, HUMIDITY, PRECIPITATION};
};

void clear_colours (Planet_colours&);
void init_colours (Planet_colours&, const Grid&);
void set_colours (Planet_colours&, const Grid&, const Terrain&, int);
void set_colours (Planet_colours&, const Grid&, const Terrain&, const Season*, int);
void colour_topography (Planet_colours&, const Grid&, const Terrain&);
void colour_vegetation (Planet_colours&, const Grid&, const Terrain&, const Season&);
void colour_temperature (Planet_colours&, const Grid&, const Season&);
void colour_aridity (Planet_colours&, const Grid&, const Terrain&, const Season&);
void colour_humidity (Planet_colours&, const Grid&, const Terrain&, const Season&);
void colour_precipitation (Planet_colours&, const Grid&, const Terrain&, const Season&);

}

#endif
