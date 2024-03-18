#ifndef climate_tile_h
#define climate_tile_h

namespace earthgen {

class Wind {
public:
	Wind () :
		direction (0), speed (0) {}

	double direction;
	double speed;
};

class Climate_tile {
public:
	Climate_tile () :
		temperature (0), humidity (0), precipitation (0) {}

	Wind wind;
	double temperature;
	double humidity;
	double precipitation;
};

class Climate_edge {
public:
	Climate_edge () :
		wind_velocity (0) {}

	double wind_velocity;
};

inline double temperature (const Climate_tile& t) {return t.temperature;}
inline double humidity (const Climate_tile& t) {return t.humidity;}
inline double precipitation (const Climate_tile& t) {return t.precipitation;}

double aridity (const Climate_tile&);
double potential_evapotranspiration (const Climate_tile&);

inline double wind_velocity (const Climate_edge& e) {return e.wind_velocity;}

}

#endif
