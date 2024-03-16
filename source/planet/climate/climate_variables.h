#ifndef climate_variables_h
#define climate_variables_h

namespace earthgen {

class Climate;

class Climate_variables {
public:
	Climate_variables () {}

	int season_count;
};

int season_count (const Climate&);

}

#endif
