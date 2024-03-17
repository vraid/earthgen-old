#include <math.h>
#include "climate.h"

namespace earthgen {

void clear_climate (Climate& climate) {
	climate.seasons.clear();
	climate.var.season_count = 0;
}

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

}
