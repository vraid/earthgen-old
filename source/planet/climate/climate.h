#ifndef climate_h
#define climate_h

#include <deque>
#include "season.h"
#include "climate_parameters.h"

namespace earthgen {

class Climate_variables {
public:
	Climate_variables () {}

	int season_count;
};

class Climate {
public:
	Climate () {}

	Climate_variables var;
	std::deque<Season> seasons;
};

inline const std::deque<Season> seasons (const Climate& climate) {return climate.seasons;}
inline const Season& nth_season (const Climate& climate, int n) {return climate.seasons[n];}
inline Season& m_season (Climate& climate, int n) {return climate.seasons[n];}

inline int season_count (const Climate& climate) {return climate.var.season_count;}

void clear_climate (Climate&);

float freezing_point ();
float temperature_lapse_rate ();
// lapse of elevation
float temperature_lapse (float);

// saturation at temperature
float saturation_humidity (float);
// aridity at temperature
float aridity (float);

}

#endif
