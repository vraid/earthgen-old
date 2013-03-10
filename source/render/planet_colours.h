#ifndef planet_colours_h
#define planet_colours_h

#include <deque>
#include "colour.h"
class Planet;
class Season;

class Planet_colours {
public:
	Planet_colours () {}

	std::deque<Colour> tiles;

	enum {TOPOGRAPHY, VEGETATION, TEMPERATURE, ARIDITY, HUMIDITY, PRECIPITATION};
};

void clear_colours (Planet_colours&);
void init_colours (Planet_colours&, const Planet&);
void set_colours (Planet_colours&, const Planet&, int);
void set_colours (Planet_colours&, const Planet&, const Season*, int);
void colour_topography (Planet_colours&, const Planet&);
void colour_vegetation (Planet_colours&, const Planet&, const Season&);
void colour_temperature (Planet_colours&, const Planet&, const Season&);
void colour_aridity (Planet_colours&, const Planet&, const Season&);
void colour_humidity (Planet_colours&, const Planet&, const Season&);
void colour_precipitation (Planet_colours&, const Planet&, const Season&);

#endif