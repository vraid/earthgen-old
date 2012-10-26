#include "climate.h"
#include "../planet.h"
#include "../../math/vector2.h"
#include <algorithm>
#include <cmath>

namespace climate {

void init (Planet* p) {
	Climate* c = p->climate;
	c->tile.resize(grid::tiles(p)*seasons(p));
	c->corner.resize(grid::corners(p)*seasons(p));
	c->edge.resize(grid::edges(p)*seasons(p));
}

int seasons (const Planet* p) {
	return p->climate->var.seasons;
}

double time_of_year (const Planet* p, int season) {
	return (double)season/(double)seasons(p);
}

double solar_equator (const Planet* p, int season) {
	return p->terrain->var.axial_tilt * sin(2.0*pi*time_of_year(p, season));
}

double sunlight (const Planet* p, double latitude, int season) {
	return std::max(0.0, cos(latitude - solar_equator(p, season)));
}

double air_density (const Planet*, double temperature) {
	return 353.0/temperature;
}

double saturation_humidity (const Planet* p, double temperature) {
	double c = 4.6e-9;
	double k = 0.05174;
	return c*exp(k*temperature);
}

double dry_adiabatic_lapse_rate (const Planet* p) {
	return -0.0098;
}

double temperature_lapse (const Planet* p, double temperature, double humidity, double altitude, double epsilon) {
	double dry_adiabatic_lapse_rate = -0.0098; /* K/m */
	double latent_water_heat = 2.5; /* kJ/kg */
	double density = air_density(p, temperature); /* kg/m^3 */
	double air_heat_capacity = 1.0; /* kJ/kg/K */
	double dry_lapse = dry_adiabatic_lapse_rate * altitude; /* K */
	/* no condensation */
	if (altitude <= 0) {
		return dry_lapse;
	}
	else if (humidity <= saturation_humidity(p, temperature + dry_lapse)) {
		return dry_lapse;
	}
	/* condensation */
	else {
		double upper_condensation = (humidity - saturation_humidity(p, temperature + dry_lapse)) / humidity;
		double lower_condensation = 0.0;
		double upper_lapse = dry_lapse + (latent_water_heat /* kJ/kg */ * humidity * upper_condensation /* kJ/m^3 */ / density /* kJ/kg */ * air_heat_capacity /* K */);
		double lower_lapse = dry_lapse;
		
		while (saturation_humidity(p, temperature + upper_lapse) > humidity * (1.0 - upper_condensation) * (1.0 + epsilon)) {
			double mid_condensation = (upper_condensation + lower_condensation)/2.0;
			double mid_lapse = dry_lapse + (latent_water_heat * humidity * mid_condensation * density * air_heat_capacity);
			
			if (saturation_humidity(p, temperature + mid_lapse) >= humidity * (1.0 - mid_condensation)) {
				upper_condensation = mid_condensation;
				upper_lapse = mid_lapse;
			}
			else {
				lower_condensation = mid_condensation;
				lower_lapse = mid_lapse;
			}
		}
		return upper_lapse;
	}
}

const Climate_tile* tile (const Planet* p, int id, int season) {
	return &p->climate->tile[seasons(p)*season + id];
}
const Climate_tile* tile (const Planet* p, const Tile* t, int season) {
	return tile(p, t->id, season);
}
const Climate_corner* corner (const Planet* p, int id, int season) {
	return &p->climate->corner[seasons(p)*season + id];
}
const Climate_corner* corner (const Planet* p, const Corner* c, int season) {
	return corner(p, c->id, season);
}
const Climate_edge* edge (const Planet* p, int id, int season) {
	return &p->climate->edge[seasons(p)*season + id];
}
const Climate_edge* edge (const Planet* p, const Edge* e, int season) {
	return edge(p, e->id, season);
}
Climate_tile* m_tile (Planet* p, int id, int season) {
	return &p->climate->tile[seasons(p)*season + id];
}
Climate_corner* m_corner (Planet* p, int id, int season) {
	return &p->climate->corner[seasons(p)*season + id];
}
Climate_edge* m_edge (Planet* p, int id, int season) {
	return &p->climate->edge[seasons(p)*season + id];
}

}
