#include "vector2.h"
#include <cmath>

Vector2::Vector2 () {
	x = 0;
	y = 0;
}

Vector2::Vector2 (double a, double b) {
	x = a;
	y = b;
}

Vector2& Vector2::operator = (const Vector2& v) {
	x = v.x;
	y = v.y;
	return *this;
}

Vector2 Vector2::operator + (const Vector2& v) const {
	return Vector2(x+v.x, y+v.y);
}

Vector2 Vector2::operator - (const Vector2& v) const {
	return Vector2(x-v.x, y-v.y);
}

Vector2 Vector2::operator * (double d) const {
	return Vector2(x*d, y*d);
}

Vector2 Vector2::operator / (double d) const {
	return Vector2(x/d, y/d);
}

namespace vector2 {

double angle (const Vector2& v) {
	return atan2(v.y, v.x);
}

double length (const Vector2& v) {
	return sqrt(v.x*v.x + v.y*v.y);
}

Vector2 rotate (const Vector2& v, double a) {
	return Vector2(v.x*cos(a) + v.y*sin(a), v.y*cos(a) - v.x*sin(a));
}

}
