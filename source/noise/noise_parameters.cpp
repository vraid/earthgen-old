#include "noise_parameters.h"

Noise_parameters::Noise_parameters () {
	octaves = 1.0;
	amplitude = 1.0;
	frequency = 1.0;
	scale = 1.0;
	mod = 1.0;
	offset = Vector4(0,0,0,0);
}

Noise_parameters::Noise_parameters (int oct, double amp, double freq, double sc, const Vector4& v) {
	octaves = oct;
	amplitude = amp;
	frequency = freq;
	scale = sc;
	double range = 0;
	double a = 1.0;
	for (int i=0; i<octaves; i++) {
		range += a;
		a /= amplitude;
	}
	mod = 1.0/range;
	offset = v;
}

Noise_parameters& Noise_parameters::operator = (const Noise_parameters& par) {
	octaves = par.octaves;
	amplitude = par.amplitude;
	frequency = par.frequency;
	scale = par.scale;
	mod = par.mod;
	offset = par.offset;
	return *this;
}
