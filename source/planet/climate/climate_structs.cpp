#include "climate_structs.h"
#include "climate.h"

namespace earthgen {

double aridity (const Climate_tile& t) {
	return aridity(potential_evapotranspiration(t));
}

double potential_evapotranspiration (const Climate_tile& t) {
	return saturation_humidity(temperature(t)) - humidity(t);
}

}
