#include "vector3.h"
#include "math_common.h"
#include <cmath>

namespace earthgen {

Vector3::Vector3 () :
	values ({{0, 0, 0}}) {}

Vector3::Vector3 (double a, double b, double c) :
	values ({{a, b, c}}) {}

bool Vector3::operator == (const Vector3& v) const {
	auto eq = [=](int n) { return at(n) == v.at(n); };
	return (eq(0) && eq(1) && eq(2));
}

bool Vector3::operator != (const Vector3& v) const {
	return !operator==(v);
}

Vector3 Vector3::operator + (const Vector3& v) const {
	auto sum = [=](int n) { return at(n) + v.at(n); };
	return Vector3(sum(0), sum(1), sum(2));
}

Vector3 Vector3::operator - (const Vector3& v) const {
	auto sub = [=](int n) { return at(n) - v.at(n); };
	return Vector3(sub(0), sub(1), sub(2));
}

Vector3 Vector3::operator * (double d) const {
	return Vector3(x()*d, y()*d, z()*d);
}

bool zero (const Vector3& v) {
	auto z = [=](int n) { return v.at(n) == 0.0; };
	return (z(0) && z(1) && z(2));
}

bool parallel (const Vector3& v, const Vector3& u) {
	return zero(cross_product(v,u));
}

Vector3 normal (const Vector3& v) {
	double d = 1.0 / length(v);
	return v*d;
}

Vector3 cross_product (const Vector3& v, const Vector3& u) {
	auto prod = [=](int n, int k) { return v.at(n) * u.at(k); };
	return Vector3(
		prod(1, 2) - prod(2, 1),
		prod(2, 0) - prod(0, 2),
		prod(0, 1) - prod(1, 0));
}

double dot_product (const Vector3& v, const Vector3& u) {
	auto prod = [=](int n) { return v.at(n) * u.at(n); };
	return prod(0) + prod(1) + prod(2);
}

double length (const Vector3& v) {
	return std::sqrt(squared_length(v));
}

double squared_length (const Vector3& v) {
	return square(v.x()) + square(v.y()) + square(v.z());
}

double distance (const Vector3& v, const Vector3& u) {
	return std::sqrt(squared_distance(v,u));
}

double squared_distance (const Vector3& v, const Vector3& u) {
	return squared_length(v - u);
}

double angle (const Vector3& v, const Vector3& u) {
	return std::acos(dot_product(v,u) / (length(v) * length(u)));
}

}
