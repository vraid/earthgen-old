#ifndef noise_h
#define noise_h

#include "noise_parameters.h"
#include "simplex_noise.h"

class Vector3;

namespace noise {
	double noise (const Noise_parameters&, const Vector3&);
}

#endif
