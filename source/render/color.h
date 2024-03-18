#ifndef color_h
#define color_h

#include <array>

namespace earthgen {

class Color {
public:
	Color () :
		values ({0, 0, 0}) {}
		
	Color (double r, double g, double b) :
		values ({r, g, b}) {}

	double at (int n) const {return values[n];};
	double r () const {return at(0);};
	double g () const {return at(1);};
	double b () const {return at(2);};

private:
	std::array<double, 3> values;
};

Color interpolate (const Color&, const Color&, double);

}

#endif
