#ifndef climate_generation_h
#define climate_generation_h

#include <vector>
#include "climate_structs.h"

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
	double latitude;
	double temperature;
	double humidity;
	double precipitation;
};

class Climate_generation_edge {
public:
	Climate_generation_edge () :
		wind_velocity (0) {}

	double wind_velocity;
};

class Season_variables {
public:
	Season_variables () {}
	~Season_variables () {}

	double time_of_year;
	double solar_equator;
};

class Climate_generation_season {
public:
	Climate_generation_season () :
		tropical_equator (0) {}

	Season_variables var;
	double tropical_equator;

	std::vector<Climate_generation_tile> tiles;
	std::vector<Climate_generation_edge> edges;
};

void generate_climate (Climate&, Terrain&, const Grid&, const Climate_parameters&);
void generate_season (Climate&, const Terrain&, const Grid&, const Climate_parameters&, double);

void _set_temperature (const Terrain&, const Grid&, const Climate_parameters&, Climate_generation_season&);
void _set_wind (const Terrain&, const Grid&, const Climate_parameters&, Climate_generation_season&);
void _set_humidity (const Terrain&, const Grid&, const Climate_parameters&, Climate_generation_season&);

}

#endif
