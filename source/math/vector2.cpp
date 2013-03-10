#include "vector2.h"
#include <cmath>

Vector2::Vector2 () :
	x (0), y (0) {}

Vector2::Vector2 (float a, float b) :
	x (a), y (b) {}

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

double length (const Vector2& v) {
	return sqrt(squared_length(v));
}
double squared_length (const Vector2& v) {
	return v.x*v.x + v.y*v.y;
}

double distance (const Vector2& v, const Vector2& u) {
	return sqrt(squared_distance(v, u));
}
double squared_distance (const Vector2& v, const Vector2& u) {
	return squared_length(v - u);
}
double angle (const Vector2& v) {
	return atan2(v.y, v.x);
}