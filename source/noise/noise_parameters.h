#ifndef noise_parameters_h
#define noise_parameters_h

#include "../math/vector4.h"

class Noise_parameters {
public:
	Noise_parameters ();
	Noise_parameters (int, double, double, double, const Vector4&);
	~Noise_parameters() {};

	Noise_parameters& operator = (const Noise_parameters&);

	int octaves;
	double amplitude;
	double frequency;
	double scale;
	double mod;
	Vector4 offset;
};

namespace noise {
	void load_parameters (Noise_parameters*);
}

#endif
