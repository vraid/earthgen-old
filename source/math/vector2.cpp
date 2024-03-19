#include "vector2.h"
#include "math_common.h"
#include <cmath>

namespace earthgen {

Vector2::Vector2 () :
	values ({{0, 0}}) {}

Vector2::Vector2 (double a, double b) :
	values ({{a, b}}) {}

Vector2 Vector2::operator + (const Vector2& v) const {
	auto sum = [=](int n) { return at(n) + v.at(n); };
	return Vector2(sum(0), sum(1));
}

Vector2 Vector2::operator - (const Vector2& v) const {
	auto sub = [=](int n) { return at(n) - v.at(n); };
	return Vector2(sub(0), sub(1));
}

Vector2 Vector2::operator * (double d) const {
	return Vector2(x()*d, y()*d);
}

double length (const Vector2& v) {
	return std::sqrt(squared_length(v));
}

double squared_length (const Vector2& v) {
	return square(v.x()) + square(v.y());
}

double distance (const Vector2& v, const Vector2& u) {
	return std::sqrt(squared_distance(v, u));
}

double squared_distance (const Vector2& v, const Vector2& u) {
	return squared_length(v - u);
}

double angle (const Vector2& v) {
	return std::atan2(v.y(), v.x());
}

}
