#ifndef climate_generation_season
#define climate_generation_season

#include "season_variables.h"
#include "wind.h"
#include "../../math/vector2.h"

namespace earthgen {

class Climate_generation_tile {
public:
	Climate_generation_tile () :
		latitude (0), temperature (0), humidity (0), precipitation (0) {}
		
	Wind wind;
	float latitude;
	float temperature;
	float humidity;
	float precipitation;
};

class Climate_generation_edge {
public:
	Climate_generation_edge () :
		wind_velocity (0) {}
		
	float wind_velocity;
};

class Climate_generation_season {
public:
	Climate_generation_season () :
		tropical_equator (0) {}

	Season_variables var;
	float tropical_equator;

	std::deque<Climate_generation_tile> tiles;
	std::deque<Climate_generation_edge> edges;
};

}

#endif
