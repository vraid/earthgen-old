#include "vector3.h"
#include <math.h>

Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(double a, double b, double c) {
	x = a;
	y = b;
	z = c;
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

Vector3 Vector3::operator * (double d) const {
	return Vector3(x*d, y*d, z*d);
}

namespace vector3 {

Vector3 cross_product (const Vector3& v, const Vector3& e) {
	return Vector3(
	v.y*e.z - v.z*e.y,
	v.z*e.x - v.x*e.z,
	v.x*e.y - v.y*e.x);
}

double distance (const Vector3& v, const Vector3& e) {
	return sqrt(distance_square(v,e));
}

double distance_square (const Vector3& v, const Vector3& e) {
	double a = (v.x-e.x);
	double b = (v.y-e.y);
	double c = (v.z-e.z);
	return a*a + b*b + c*c;
}

double dot_product (const Vector3& v, const Vector3& e) {
	return v.x*e.x + v.y*e.y + v.z*e.z;
}

double length (const Vector3& v) {
	return sqrt(length_square(v));
}

double length_square (const Vector3& v) {
	return v.x*v.x + v.y*v.y + v.z*v.z;
}

Vector3 normal (const Vector3& v) {
	double d = length(v);
	return Vector3(v.x/d, v.y/d, v.z/d);
}
}	
