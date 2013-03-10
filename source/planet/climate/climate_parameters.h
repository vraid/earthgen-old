#ifndef climate_parameters_h
#define climate_parameters_h

#include <algorithm>
#include "../../math/math_common.h"

class Climate_parameters {
public:
	Climate_parameters () {
		set_default();
	}

	Climate_parameters& operator = (const Climate_parameters& par) {
		seasons = par.seasons;
		axial_tilt = par.axial_tilt;
		return *this;
	}

	void set_default () {
		seasons = 1;
		axial_tilt = 0.4;
		error_tolerance = 0.01;
	}

	void correct_values () {
		seasons = std::max(1, seasons);
		
		axial_tilt = std::max(0.0, axial_tilt);
		axial_tilt = std::min(pi/2, axial_tilt);

		error_tolerance = std::max(0.001f, error_tolerance);
		error_tolerance = std::min(1.0f, error_tolerance);
	}

	int seasons;
	double axial_tilt;
	float error_tolerance;
};

#endif