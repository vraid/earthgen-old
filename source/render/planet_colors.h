#ifndef planet_colors_h
#define planet_colors_h

#include <vector>
#include "color.h"

namespace earthgen {

class Grid;
class Terrain;
class Season;
class Climate;

class Planet_colors {
public:
	Planet_colors () {}

	std::vector<Color> tiles;

	enum {TOPOGRAPHY, VEGETATION, TEMPERATURE, ARIDITY, HUMIDITY, PRECIPITATION};
};

void clear_colors (Planet_colors&);
void init_colors (Planet_colors&, const Grid&);
void set_colors (Planet_colors&, const Grid&, const Terrain&, int);
void set_colors (Planet_colors&, const Grid&, const Terrain&, const Season*, int);
void color_topography (Planet_colors&, const Grid&, const Terrain&);
void color_vegetation (Planet_colors&, const Grid&, const Terrain&, const Season&);
void color_temperature (Planet_colors&, const Grid&, const Season&);
void color_aridity (Planet_colors&, const Grid&, const Terrain&, const Season&);
void color_humidity (Planet_colors&, const Grid&, const Terrain&, const Season&);
void color_precipitation (Planet_colors&, const Grid&, const Terrain&, const Season&);

}

#endif
