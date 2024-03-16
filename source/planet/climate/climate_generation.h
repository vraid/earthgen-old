#ifndef climate_generation_h
#define climate_generation_h

#include <vector>
#include "wind.h"

namespace earthgen {

class Grid;
class Terrain;
class Climate;
class Climate_parameters;

class Climate_generation_tile {
public:
	Climate_generation_tile () :
		latitude (0), temperature (0), humidity (0), precipitation (0) {}

	Wind wind;
	float latitude;
	float temperature;
	float humidity;
	float precipitation;
};

class Climate_generation_edge {
public:
	Climate_generation_edge () :
		wind_velocity (0) {}

	float wind_velocity;
};

class Season_variables {
public:
	Season_variables () {}
	~Season_variables () {}

	float time_of_year;
	float solar_equator;
};

class Climate_generation_season {
public:
	Climate_generation_season () :
		tropical_equator (0) {}

	Season_variables var;
	float tropical_equator;

	std::vector<Climate_generation_tile> tiles;
	std::vector<Climate_generation_edge> edges;
};

void generate_climate (Climate&, Terrain&, const Grid&, const Climate_parameters&);
void generate_season (Climate&, const Terrain&, const Grid&, const Climate_parameters&, float);

void _set_temperature (const Terrain&, const Grid&, const Climate_parameters&, Climate_generation_season&);
void _set_wind (const Terrain&, const Grid&, const Climate_parameters&, Climate_generation_season&);
void _set_humidity (const Terrain&, const Grid&, const Climate_parameters&, Climate_generation_season&);

}

#endif
