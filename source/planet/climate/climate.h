#ifndef climate_h
#define climate_h

#include <vector>
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
	std::vector<Season> seasons;
};

inline const std::vector<Season> seasons (const Climate& climate) {return climate.seasons;}
inline const Season& nth_season (const Climate& climate, int n) {return climate.seasons[n];}
inline Season& m_season (Climate& climate, int n) {return climate.seasons[n];}

inline int season_count (const Climate& climate) {return climate.var.season_count;}

void clear_climate (Climate&);

double freezing_point ();
double temperature_lapse_rate ();
// lapse of elevation
double temperature_lapse (double);

// saturation at temperature
double saturation_humidity (double);
// aridity at temperature
double aridity (double);

}

#endif
