#ifndef climate_edge_h
#define climate_edge_h

namespace earthgen {

class Climate_edge {
public:
	Climate_edge () :
		wind_velocity (0) {}

	float wind_velocity;
};

inline float wind_velocity (const Climate_edge& e) {return e.wind_velocity;}

}

#endif
