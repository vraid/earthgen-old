#include "vector4.h"

Vector4::Vector4 () {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4 (double a, double b, double c, double d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

Vector4& Vector4::operator = (const Vector4& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}
