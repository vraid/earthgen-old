#ifndef climate_h
#define climate_h

class Planet;

class Climate {
public:
	Climate();
	~Climate();
};

namespace climate {
	double solar_equator (const Planet*, double);
	double thermal_equator (const Planet*, double);
}

#endif
