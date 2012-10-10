#ifndef climate_tile_h
#define climate_tile_h

#include "wind.h"

class Climate_tile {
public:
	Climate_tile () {
		temperature = 0.0;
		humidity = 0.0;
		precipitation = 0.0;
	}
	~Climate_tile () {};

	float temperature;
	float humidity;
	float precipitation;
	Wind wind;
};

#endif
