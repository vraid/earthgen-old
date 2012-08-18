#include "quaternion.h"
#include "vector3.h"
#include "matrix3.h"
#include <math.h>

Quaternion::Quaternion () {
	w = 1;
	x = 0;
	y = 0;
	z = 0;
}

Quaternion::Quaternion (double angle, const Vector3& axis) {
	Vector3 vec = vector3::normal(axis);
	w = cos(angle*0.5);
	vec = vec*sin(angle*0.5);
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Quaternion::Quaternion (const Vector3& v, const Vector3& e) {
	Vector3 axis = vector3::cross_product(v, e);
	double angle = acos(vector3::dot_product(v, e) / (vector3::length(v)*vector3::length(e)));
	*this = Quaternion(angle, axis);
}

Quaternion::Quaternion (double alpha, double i, double j, double k) {
	w = alpha;
	x = i;
	y = j;
	z = k;
}

Quaternion& Quaternion::operator = (const Quaternion &q) {
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
	return *this;
}

Quaternion Quaternion::operator * (const Quaternion& q) const {
	return Quaternion(w*q.w - vector3::dot_product(quaternion::vector(*this), quaternion::vector(q)),
		y*q.z - z*q.y + w*q.x + x*q.w,
		z*q.x - x*q.z + w*q.y + y*q.w,
		x*q.y - y*q.x + w*q.z + z*q.w);
}

Vector3 Quaternion::operator * (const Vector3 &v) const {
	Quaternion vec_quat(0, v.x, v.y, v.z);
	Quaternion res_quat;
	
	res_quat = vec_quat * quaternion::conjugate(*this);
	res_quat = (*this) * res_quat;
	
	return quaternion::vector(res_quat);
}

Quaternion quaternion::conjugate (const Quaternion& q) {
	return Quaternion(q.w,-q.x,-q.y,-q.z);
}

Quaternion quaternion::normal (const Quaternion& q) {
	double d = sqrt(q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z);
	return Quaternion(q.w/d, q.x/d, q.y/d, q.z/d);
}

Vector3 quaternion::vector (const Quaternion& q) {
	return Vector3(q.x,q.y,q.z);
}

Matrix3 quaternion::matrix (const Quaternion& q) {
	Matrix3 a;
	a.m[0][0] = 1 - 2*q.y*q.y - 2*q.z*q.z;
	a.m[0][1] = 2*q.x*q.y - 2*q.z*q.w;
	a.m[0][2] = 2*q.x*q.z + 2*q.y*q.w;
	a.m[1][0] = 2*q.x*q.y + 2*q.z*q.w;
	a.m[1][1] = 1 - 2*q.x*q.x - 2*q.z*q.z;
	a.m[1][2] = 2*q.y*q.z - 2*q.x*q.w;
	a.m[2][0] = 2*q.x*q.z - 2*q.y*q.w;
	a.m[2][1] = 2*q.y*q.z + 2*q.x*q.w;
	a.m[2][2] = 1 - 2*q.x*q.x - 2*q.y*q.y;
	return a;
}
