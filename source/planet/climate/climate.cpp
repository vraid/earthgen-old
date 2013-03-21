#include "climate.h"
#include "../planet.h"

void clear_climate (Planet& p) {
	std::deque<Season>().swap(m_climate(p).seasons);
	m_climate(p).var.season_count = 0;
}

const Climate& climate (const Planet& p) {return *p.climate;}
Climate& m_climate (Planet& p) {return *p.climate;}

const std::deque<Season> seasons (const Planet& p) {return climate(p).seasons;}
const Season& nth_season (const Planet& p, int n) {return climate(p).seasons[n];}
Season& m_season (Planet& p, int n) {return m_climate(p).seasons[n];}

float freezing_point () {return 273.15;}
float temperature_lapse_rate () {return 9.8e-3;}
float temperature_lapse (float height) {
	return height * temperature_lapse_rate();
}

float saturation_humidity (float temperature) {
	double c = 4.6e-9;
	double k = 0.05174;
	return c*exp(k*temperature);
}

float aridity (float potential_evapotranspiration) {
	float index_base_temperature = 10 + freezing_point();
	return potential_evapotranspiration / saturation_humidity(index_base_temperature);
}