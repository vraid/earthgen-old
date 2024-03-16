#ifndef climate_h
#define climate_h

#include <deque>
#include "season.h"
#include "climate_variables.h"
#include "climate_parameters.h"

namespace earthgen {

class Climate {
public:
	Climate () {}

	Climate_variables var;
	std::deque<Season> seasons;
};

const std::deque<Season> seasons (const Climate&);
const Season& nth_season (const Climate&, int);
Season& m_season (Climate&, int);

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
