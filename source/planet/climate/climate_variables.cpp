#include "climate_variables.h"
#include "../planet.h"

namespace earthgen {

int season_count (const Planet& p) {return climate(p).var.season_count;}

}
