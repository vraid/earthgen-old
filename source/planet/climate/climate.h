#ifndef climate_h
#define climate_h

#include <deque>
#include "season.h"
#include "climate_variables.h"
#include "climate_parameters.h"
class Planet;

class Climate {
public:
	Climate () {}

	Climate_variables var;
	std::deque<Season> seasons;
};

const Climate& climate (const Planet&);
Climate& m_climate (Planet&);

const std::deque<Season> seasons (const Planet&);
const Season& nth_season (const Planet&, int);
Season& m_season (Planet&, int);

void clear_climate (Planet&);

float freezing_point ();
float temperature_lapse_rate ();
// lapse of elevation
float temperature_lapse (float);

// saturation at temperature
float saturation_humidity (float);
// aridity at temperature
float aridity (float);

#endif
