#ifndef climate_edge_h
#define climate_edge_h

class Climate_edge {
public:
	Climate_edge () :
		wind_velocity (0), river_flow (0) {}

	float wind_velocity;
	float river_flow;
};

float wind_velocity (const Climate_edge&);
float river_flow (const Climate_edge&);

#endif
