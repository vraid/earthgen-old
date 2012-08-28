#ifndef parameters_h
#define parameters_h

#include <string>
#include "../noise/noise_parameters.h"

#define nullptr NULL

class Vector3;
class Noise_parameters;

class Parameters {
public:
	Parameters();
	~Parameters();
	Parameters& operator = (const Parameters&);

	int mesh_size;

	//physical
	double axial_tilt;
	Vector3* axis;

	//terrain
	std::string terrain_seed;
	Noise_parameters terrain_noise;
	double elevation_scale;
	double water_ratio;

	//climate
	int seasons;
};

namespace parameters {
	Parameters* load ();
	Parameters* load (std::string);
	void save (const Parameters*, std::string);
	double check_range_float (double, const double*);
	int check_range_int (int, const int*);

	const int mesh_size_range[2] = {0, 11};
	const double axial_tilt_range[2] = {0.0, 0.8};
	const double elevation_scale_range[2] = {1.0, 100000.0};
	const double water_ratio_range[2] = {0.0,1.0};
	const int seasons_range[2] = {1,24};
	const int octaves_range[2] = {1,10};
	const double amplitude_range[2] = {0.1, 10.0};
	const double frequency_range[2] = {0.1, 10.0};
	const double scale_range[2] = {0.0001, 1000000.0};
}

#endif
