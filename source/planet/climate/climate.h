#ifndef climate_h
#define climate_h

class Planet;
class Tile;
class Corner;
class Edge;
#include "climate_variables.h"
#include "climate_tile.h"
#include "climate_corner.h"
#include "climate_edge.h"
#include <vector>

class Climate {
public:
	Climate() {};
	~Climate() {};

	Climate_variables var;
	std::vector<Climate_tile> tile;
	std::vector<Climate_corner> corner;
	std::vector<Climate_edge> edge;
};

namespace climate {
	void init (Planet*);

	/* planet -> seasons [1..] */
	int seasons (const Planet*);
	/* planet -> season -> time [0, 1) */
	double time_of_year (const Planet*, int season);
	/* planet -> season -> longitude */
	double solar_equator (const Planet*, int season);
	/* planet -> season -> longitude */
	double thermal_equator (const Planet*, int season);
	/* planet -> latitude -> season -> sunlight [0, 1] */
	double sunlight (const Planet* p, double latitude, int season);
	/* planet -> temperature K -> density kg/m^3 */
	double air_density (const Planet*, double temperature);
	/* planet -> temperature K -> humidity kg/m^3 */
	double saturation_humidity (const Planet*, double temperature);
	/* planet -> temperature/altitude K/m */
	double dry_adiabatic_lapse_rate (const Planet*);
	/* planet -> temperature K -> humidity kg/m^3 -> altitude m -> epsilon -> temperature K */
	double temperature_lapse (const Planet*, double temperature, double humidity, double altitude, double epsilon);
	
	const Climate_tile* tile (const Planet*, int id, int season);
	const Climate_tile* tile (const Planet*, const Tile*, int season);
	const Climate_corner* corner (const Planet*, int id, int season);
	const Climate_corner* corner (const Planet*, const Corner*, int season);
	const Climate_edge* edge (const Planet*, int id, int season);
	const Climate_edge* edge (const Planet*, const Edge*, int season);
	Climate_tile* m_tile (Planet*, int id, int season);
	Climate_corner* m_corner (Planet*, int id, int season);
	Climate_edge* m_edge (Planet*, int id, int season);
}

#endif
