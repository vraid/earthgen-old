#include "color.h"

namespace earthgen {

Color interpolate (const Color& a, const Color& b, double d) {
	auto inter = [=](int n) {return a.at(n)*(1-d) + b.at(n)*d;};
	return Color(inter(0), inter(1), inter(2));
}

}
