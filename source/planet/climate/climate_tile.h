#ifndef climate_tile_h
#define climate_tile_h
#include "wind.h"

namespace earthgen {

class Climate_tile {
public:
	Climate_tile () :
		temperature (0), humidity (0), precipitation (0) {}

	Wind wind;
	float temperature;
	float humidity;
	float precipitation;
};

inline float temperature (const Climate_tile& t) {return t.temperature;}
inline float humidity (const Climate_tile& t) {return t.humidity;}
inline float precipitation (const Climate_tile& t) {return t.precipitation;}

float aridity (const Climate_tile&);
float potential_evapotranspiration (const Climate_tile&);

}

#endif
