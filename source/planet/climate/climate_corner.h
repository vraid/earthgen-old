#ifndef climate_corner_h
#define climate_corner_h

class Climate_corner {
public:
	Climate_corner () :
		river_flow_increase (0) {}

	float river_flow_increase;
};

float river_flow_increase (const Climate_corner&);

#endif
