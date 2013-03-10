#ifndef terrain_parameters_h
#define terrain_parameters_h

#include <string>
#include <algorithm>
#include "../../math/vector3.h"

class Terrain_parameters {
public:
	Terrain_parameters () {
		set_default();
	}

	int grid_size;
	Vector3 axis;
	std::string seed;
	int iterations;
	double water_ratio;

	Terrain_parameters& operator = (const Terrain_parameters& par) {
		grid_size = par.grid_size;
		axis = par.axis;
		seed = par.seed;
		iterations = par.iterations;
		water_ratio = par.water_ratio;
		return *this;
	}

	void set_default () {
		grid_size = 6;
		axis = Vector3(0,0,1);
		iterations = 1000;
		water_ratio = 0.65;
	}

	void correct_values () {
		grid_size = std::max(0, grid_size);
		grid_size = std::min(10, grid_size);

		if (zero(axis))
			axis = Vector3(0,0,1);
		else {
			axis = normal(axis);
		}

		iterations = std::max(0, iterations);

		water_ratio = std::max(0.0, water_ratio);
		water_ratio = std::min(1.0, water_ratio);
	}
};

#endif