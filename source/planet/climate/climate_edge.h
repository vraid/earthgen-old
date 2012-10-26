#ifndef climate_edge_h
#define climate_edge_h

class Climate_edge {
public:
	Climate_edge () {
		river_discharge = 0.0;
		wind_speed = 0.0;
	}
	~Climate_edge () {};

	float river_discharge;
	float wind_speed;
};

#endif
