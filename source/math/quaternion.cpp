#include "quaternion.h"
#include "vector3.h"
#include "matrix3.h"
#include <cmath>

Quaternion::Quaternion () :
	a (1), i (0), j (0), k(0) {}
	
Quaternion::Quaternion (const Vector3& axis, double angle) {
	Vector3 v = normal(axis);
	a = cos(angle*0.5);
	v = v*sin(angle*0.5);
	i = v.x;
	j = v.y;
	k = v.z;
}
Quaternion::Quaternion (const Vector3& a, const Vector3& b) {
	Vector3 v = normal(a);
	Vector3 u = normal(b);
	Quaternion q = Quaternion();
	if (parallel(v,u)) {
		if (v != u) {
			Vector3 inter = parallel(v,Vector3(1,0,0)) ? Vector3(0,1,0) : Vector3(1,0,0);
			q = Quaternion(inter,u) * Quaternion(v,inter);
		}
	}
	else
		q = Quaternion(cross_product(u,v), -std::acos(dot_product(v,u)));
	*this = q;
}

Quaternion::Quaternion (double alpha, double x, double y, double z) :
	a (alpha), i (x), j (y), k (z) {
}

Quaternion& Quaternion::operator = (const Quaternion& q) {
	a = q.a;
	i = q.i;
	j = q.j;
	k = q.k;
	return *this;
}

Quaternion Quaternion::operator * (const Quaternion& q) const {
	return normal(Quaternion(a*q.a - dot_product(vector(*this), vector(q)),
		j*q.k - k*q.j + a*q.i + i*q.a,
		k*q.i - i*q.k + a*q.j + j*q.a,
		i*q.j - j*q.i + a*q.k + k*q.a));
}
Vector3 Quaternion::operator * (const Vector3 &v) const {
	if (zero(v)) return v;
	Quaternion vec_quat(0, v.x, v.y, v.z);
	Quaternion res_quat;
	
	res_quat = vec_quat * conjugate(*this);
	res_quat = (*this) * res_quat;
	
	return vector(res_quat);
}

Quaternion conjugate (const Quaternion& q) {
	return Quaternion(q.a, -q.i, -q.j, -q.k);
}
Vector3 vector (const Quaternion& q) {
	return Vector3(q.i, q.j, q.k);
}
Quaternion normal (const Quaternion& q) {
	double d = sqrt(q.a*q.a + q.i*q.i + q.j*q.j + q.k*q.k);
	return Quaternion(q.a/d, q.i/d, q.j/d, q.k/d);
}

Matrix3 matrix3 (const Quaternion& q) {
	Matrix3 m;
	m.m[0][0] = 1 - 2*q.j*q.j - 2*q.k*q.k;
	m.m[0][1] = 2*q.i*q.j - 2*q.k*q.a;
	m.m[0][2] = 2*q.i*q.k + 2*q.j*q.a;
	m.m[1][0] = 2*q.i*q.j + 2*q.k*q.a;
	m.m[1][1] = 1 - 2*q.i*q.i - 2*q.k*q.k;
	m.m[1][2] = 2*q.j*q.k - 2*q.i*q.a;
	m.m[2][0] = 2*q.i*q.k - 2*q.j*q.a;
	m.m[2][1] = 2*q.j*q.k + 2*q.i*q.a;
	m.m[2][2] = 1 - 2*q.i*q.i - 2*q.j*q.j;
	return m;
}
