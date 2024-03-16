#ifndef color_h
#define color_h

namespace earthgen {

class Color {
public:
	Color () :
		r (0), g (0), b (0) {}
		
	Color (float rv, float gv, float bv) :
		r (rv), g (gv), b (bv) {}

	Color& operator = (const Color& c) {
		r = c.r;
		g = c.g;
		b = c.b;
		return *this;
	}

	float r;
	float g;
	float b;
};

Color interpolate (const Color&, const Color&, double);

}

#endif
