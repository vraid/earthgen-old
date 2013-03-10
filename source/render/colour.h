#ifndef colour_h
#define colour_h

class Colour {
public:
	Colour () :
		r (0), g (0), b (0) {}
		
	Colour (float rv, float gv, float bv) :
		r (rv), g (gv), b (bv) {}

	Colour& operator = (const Colour& c) {
		r = c.r;
		g = c.g;
		b = c.b;
		return *this;
	}

	float r;
	float g;
	float b;
};

Colour interpolate (const Colour&, const Colour&, double);

#endif