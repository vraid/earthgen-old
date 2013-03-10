#include "climate_tile.h"
#include "climate.h"

float temperature (const Climate_tile& t) {return t.temperature;}
float humidity (const Climate_tile& t) {return t.humidity;}
float aridity (const Climate_tile& t) {
	return aridity(potential_evapotranspiration(t));
}
float potential_evapotranspiration (const Climate_tile& t) {
	return saturation_humidity(temperature(t)) - humidity(t);
}
float precipitation (const Climate_tile& t) {return t.precipitation;}