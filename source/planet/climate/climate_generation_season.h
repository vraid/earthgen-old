#ifndef climate_generation_season
#define climate_generation_season

#include "season_variables.h"
#include "wind.h"
#include "../../math/vector2.h"

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

class Climate_generation_corner {
public:
	Climate_generation_corner () :
		river_flow (0), river_flow_increase (0) {}
		
	float river_flow;
	float river_flow_increase;
};

class Climate_generation_edge {
public:
	Climate_generation_edge () :
		river_flow (0), wind_velocity (0) {}
		
	float river_flow;
	float wind_velocity;
};

class Climate_generation_season {
public:
	Climate_generation_season () :
		tropical_equator (0) {}

	Season_variables var;
	float tropical_equator;

	std::deque<Climate_generation_tile> tiles;
	std::deque<Climate_generation_corner> corners;
	std::deque<Climate_generation_edge> edges;
};

#endif