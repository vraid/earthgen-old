#include "color.h"

namespace earthgen {

Color interpolate (const Color& a, const Color& b, double d) {
	return Color(a.r*(1-d) + b.r*d, a.g*(1-d) + b.g*d, a.b*(1-d) + b.b*d);
}

}
