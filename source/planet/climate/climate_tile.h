#ifndef climate_tile_h
#define climate_tile_h
#include "wind.h"

class Climate_tile {
public:
	Climate_tile () :
		temperature (0), humidity (0), precipitation (0) {}

	Wind wind;
	float temperature;
	float humidity;
	float precipitation;
};

float temperature (const Climate_tile&);
float humidity (const Climate_tile&);
float aridity (const Climate_tile&);
float potential_evapotranspiration (const Climate_tile&);
float precipitation (const Climate_tile&);

#endif
