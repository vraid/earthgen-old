#ifndef climate_simulation_h
#define climate_simulation_h

#include "../../math/vector2.h"
#include "wind.h"
#include <vector>

class Planet;
class Tile;

class Sim_tile {
public:
	double surface_temperature;
	double air_temperature;
	double humidity;
	double precipitation;
	Vector2 wind;
};

class Sim_corner {
public:
	double source_water;
	double river_discharge;
};

class Sim_edge {
public:
	double river_discharge;
	double wind_speed;
};

class Climate_simulation {
public:
	Climate_simulation () {};
	~Climate_simulation () {};

	int season;
	double time_of_year;
	double solar_equator;
	double precision;

	std::vector<Sim_tile> tile;
	std::vector<Sim_corner> corner;
	std::vector<Sim_edge> edge;

	std::vector<Sim_tile> ntile;
	std::vector<Sim_corner> ncorner;
	std::vector<Sim_edge> nedge;
};

namespace climate {
	void init (const Planet*, Climate_simulation*, int season);
	void iterate (const Planet*, Climate_simulation*);
	void set_wind (const Planet*, Climate_simulation*);
	void set_temperature (const Planet*, Climate_simulation*);
	void set_air_pressure (const Planet*, Climate_simulation*);
	void set_humidity (const Planet*, Climate_simulation*);
	void set_sea_distance (const Planet*, Climate_simulation*);
	void set_rivers (const Planet*, Climate_simulation*);
	void overwrite_data (const Planet*, Climate_simulation*);
	bool finished (const Planet*, const Climate_simulation*);
	double least_precision (const Climate_simulation*);
	double base_temperature (const Planet*, double latitude);
	double base_temperature (const Planet*, int id, int season);
	double pressure_gradient_force (const Planet*, const Climate_simulation*, const Tile*);
	Vector2 resulting_wind (const Planet*, const Tile*, double force);
	double net_wind (const Planet*, const Climate_simulation*, int);
}

#endif
