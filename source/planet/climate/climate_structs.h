#ifndef climate_tile_h
#define climate_tile_h

namespace earthgen {

class Wind {
public:
	Wind () :
		direction (0), speed (0) {}

	float direction;
	float speed;
};

class Climate_tile {
public:
	Climate_tile () :
		temperature (0), humidity (0), precipitation (0) {}

	Wind wind;
	float temperature;
	float humidity;
	float precipitation;
};

class Climate_edge {
public:
	Climate_edge () :
		wind_velocity (0) {}

	float wind_velocity;
};

inline float temperature (const Climate_tile& t) {return t.temperature;}
inline float humidity (const Climate_tile& t) {return t.humidity;}
inline float precipitation (const Climate_tile& t) {return t.precipitation;}

float aridity (const Climate_tile&);
float potential_evapotranspiration (const Climate_tile&);

inline float wind_velocity (const Climate_edge& e) {return e.wind_velocity;}

}

#endif
