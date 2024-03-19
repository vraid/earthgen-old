#include "climate.h"
#include <cmath>

namespace earthgen {

void clear_climate (Climate& climate) {
	climate.seasons.clear();
	climate.var.season_count = 0;
}

double freezing_point () {return 273.15;}
double temperature_lapse_rate () {return 9.8e-3;}
double temperature_lapse (double height) {
	return height * temperature_lapse_rate();
}

double saturation_humidity (double temperature) {
	double c = 4.6e-9;
	double k = 0.05174;
	return c * std::exp(k*temperature);
}

double aridity (double potential_evapotranspiration) {
	double index_base_temperature = 10 + freezing_point();
	return potential_evapotranspiration / saturation_humidity(index_base_temperature);
}

}
