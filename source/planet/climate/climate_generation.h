#ifndef climate_generation_h
#define climate_generation_h

#include "../planet.h"
#include "climate.h"
#include "climate_generation_season.h"

void generate_climate (Planet&, const Climate_parameters&);
void generate_season (Planet&, const Climate_parameters&, float);

void _set_temperature (const Planet&, const Climate_parameters&, Climate_generation_season&);
void _set_wind (const Planet&, const Climate_parameters&, Climate_generation_season&);
void _set_humidity (const Planet&, const Climate_parameters&, Climate_generation_season&);
void _set_river_flow (const Planet&, const Climate_parameters&, Climate_generation_season&);
	
#endif
