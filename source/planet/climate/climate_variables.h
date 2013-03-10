#ifndef climate_variables_h
#define climate_variables_h

class Planet;

class Climate_variables {
public:
	Climate_variables () {}

	int season_count;
};

int season_count (const Planet&);

#endif