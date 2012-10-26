#include <cmath>
#include "climate_simulation.h"
#include "../planet.h"

namespace climate {

void init (const Planet* p, Climate_simulation* sim, int season) {
	sim->season = season;
	sim->time_of_year = time_of_year(p, season);
	sim->solar_equator = solar_equator(p, season);
	for (int i=0; i<grid::tiles(p); i++) {
		sim->tile[i].surface_temperature = base_temperature(p, i, sim->solar_equator);
		sim->tile[i].air_temperature = sim->tile[i].surface_temperature;
		if (terrain::tile(p,i)->is_land) sim->tile[i].humidity = 0.0;
		else sim->tile[i].humidity = saturation_humidity(p, sim->tile[i].air_temperature);
		sim->tile[i].precipitation = 0.0;
		/* wind */
	}
}

double base_temperature (const Planet* p, double latitude) {
	return 220.0 + 70.0 * cos(latitude);
}

double base_temperature (const Planet* p, int i, int season) {
	double temp = 220.0 + 95.0 * sunlight(p, terrain::latitude(grid::tile(p,i)->v), season);
	if (terrain::tile(p,i)->is_land) temp += dry_adiabatic_lapse_rate(p) * terrain::tile(p,i)->elevation - p->terrain->var.sea_level;
	return temp;
}

}
