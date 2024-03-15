#ifndef climate_edge_h
#define climate_edge_h

namespace earthgen {

class Climate_edge {
public:
	Climate_edge () :
		wind_velocity (0) {}

	float wind_velocity;
};

float wind_velocity (const Climate_edge&);

}

#endif
