#include "colour.h"

Colour interpolate (const Colour& a, const Colour& b, double d) {
	return Colour(a.r*(1-d) + b.r*d, a.g*(1-d) + b.g*d, a.b*(1-d) + b.b*d);
}