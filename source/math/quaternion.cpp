#include "quaternion.h"
#include "vector3.h"
#include "matrix3.h"
#include "math_common.h"
#include <cmath>

namespace earthgen {

Quaternion::Quaternion () :
	values ({1, 0, 0, 0}) {}

Quaternion::Quaternion (double a, double i, double j, double k) :
	values ({a, i, j, k}) {}

Quaternion rotation_around (const Vector3& axis, double angle) {
	Vector3 v = normal(axis)*sin(angle*0.5);
	return Quaternion(cos(angle*0.5), v.x(), v.y(), v.z());
}

Quaternion rotation_between_nonparallel (const Vector3& a, const Vector3& b) {
	return rotation_around(cross_product(b,a), -std::acos(dot_product(a,b)));
}

Quaternion rotation_between_parallel (const Vector3& a, const Vector3& b) {
	if (a != b) {
		Vector3 intermediate = parallel(a,Vector3(1,0,0)) ? Vector3(0,1,0) : Vector3(1,0,0);
		return rotation_between_nonparallel(intermediate,b) * rotation_between_nonparallel(a,intermediate);
	}
	else {
		return Quaternion();
	}
}

Quaternion rotation_between (const Vector3& a, const Vector3& b) {
	Vector3 v = normal(a);
	Vector3 u = normal(b);
	return (parallel(v,u)) ? rotation_between_parallel(v, u) : rotation_between_nonparallel(v, u);
}

Quaternion Quaternion::operator * (const Quaternion& q) const {
	auto p = [=](int n, int k) { return at(n)*q.at(k); };
	return normal(
		Quaternion(
			p(0,0) - p(1,1) - p(2,2) - p(3,3),
			p(0,1) + p(1,0) + p(2,3) - p(3,2),
			p(0,2) - p(1,3) + p(2,0) + p(3,1),
			p(0,3) + p(1,2) - p(2,1) + p(3,0)));
}

Vector3 Quaternion::operator * (const Vector3 &v) const {
	return (zero(v)) ? v : vector((*this) * (Quaternion(0, v.x(), v.y(), v.z()) * conjugate(*this)));
}

Quaternion conjugate (const Quaternion& q) {
	return Quaternion(q.at(0), -q.at(1), -q.at(2), -q.at(3));
}

Vector3 vector (const Quaternion& q) {
	return Vector3(q.at(1), q.at(2), q.at(3));
}

Quaternion normal (const Quaternion& q) {
	double a = q.at(0);
	double i = q.at(1);
	double j = q.at(2);
	double k = q.at(3);
	double d = sqrt(square(a) + square(i) + square(j) + square(k));
	return Quaternion(a/d, i/d, j/d, k/d);
}

Matrix3 matrix3 (const Quaternion& q) {
	auto p = [=](int n, int k) { return q.at(n)*q.at(k); };
	Matrix3 m(
		{{{-(p(2,2) + p(3,3)), p(1,2) - p(0,3), p(1,3) + p(0,2)},
		  {p(1,2) + p(0,3), -(p(1,1) + p(3,3)), p(2,3) - p(0,1)},
		  {p(1,3) - p(0,2), p(2,3) + p(0,1), -(p(1,1) + p(2,2))}}});

	return Matrix3() + m + m;
}

}
