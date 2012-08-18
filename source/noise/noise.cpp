#include "noise.h"
#include "../math/vector3.h"

double noise::noise (const Noise_parameters& par, const Vector3& v) {
	double n = 0.0;
	double a = 1.0;
	double f = par.scale;
	for (int i=0; i<par.octaves; i++) {
		n += a*simplex_noise::noise(f*(v.x+par.offset.x), f*(v.y+par.offset.y), f*(v.z+par.offset.z), f*par.offset.w);
		a /= par.amplitude;
		f *= par.frequency;
	}
	n *= par.mod;
	return n;
}
