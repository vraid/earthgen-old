#include "vector3.h"
#include <cmath>

Vector3::Vector3 () :
	x (0), y (0), z (0) {}

Vector3::Vector3 (float a, float b, float c) :
	x (a), y (b), z (c) {}

bool Vector3::operator == (const Vector3& v) const {
	return (x == v.x && y == v.y && z == v.z);
}
bool Vector3::operator != (const Vector3& v) const {
	return !operator==(v);
}

Vector3& Vector3::operator = (const Vector3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3 Vector3::operator + (const Vector3& v) const {
	return Vector3(x+v.x, y+v.y, z+v.z);
}
Vector3 Vector3::operator - (const Vector3& v) const {
	return Vector3(x-v.x, y-v.y, z-v.z);
}
Vector3 Vector3::operator * (double d) const {
	return Vector3(x*d, y*d, z*d);
}

bool zero (const Vector3& v) {
	return (v.x == 0 && v.y == 0 && v.z == 0);
}

bool parallel (const Vector3& v, const Vector3& u) {
	return zero(cross_product(v,u));
}

Vector3 normal (const Vector3& v) {
	double d = 1.0 / length(v);
	return v*d;
}

Vector3 cross_product (const Vector3& v, const Vector3& u) {
	return Vector3(
	v.y*u.z - v.z*u.y,
	v.z*u.x - v.x*u.z,
	v.x*u.y - v.y*u.x);
}
double dot_product (const Vector3& v, const Vector3& u) {
	return v.x*u.x + v.y*u.y + v.z*u.z;
}

double length (const Vector3& v) {
	return sqrt(squared_length(v));
}
double squared_length (const Vector3& v) {
	return v.x*v.x + v.y*v.y + v.z*v.z;
}

double distance (const Vector3& v, const Vector3& u) {
	return sqrt(squared_distance(v,u));
}
double squared_distance (const Vector3& v, const Vector3& u) {
	return squared_length(v - u);
}

double angle (const Vector3& v, const Vector3& u) {
	return acos(dot_product(v,u) / (length(v) * length(u)));
}
