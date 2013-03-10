#include "matrix2.h"
#include "vector2.h"
#include <cmath>

Matrix2::Matrix2() {
	m[0][0] = 1.0;
	m[0][1] = 0.0;
	m[1][0] = 0.0;
	m[1][1] = 1.0;
}

Matrix2::Matrix2(double a[2][2]) {
	m[0][0] = a[0][0];
	m[0][1] = a[0][1];
	m[1][0] = a[1][0];
	m[1][1] = a[1][1];
}

Matrix2& Matrix2::operator = (const Matrix2& mat) {
	m[0][0] = mat.m[0][0];
	m[0][1] = mat.m[0][1];
	m[1][0] = mat.m[1][0];
	m[1][1] = mat.m[1][1];
	return *this;
}

Vector2 Matrix2::operator * (const Vector2& v) const {
	return Vector2
		(v.x*m[0][0] + v.y*m[0][1],
		 v.x*m[1][0] + v.y*m[1][1]);
}

std::vector<Vector2> Matrix2::operator * (const std::vector<Vector2>& v) const {
	std::vector<Vector2> r;
	for (int i=0; (unsigned int)i<v.size(); i++) {
		r.push_back(*this * v[i]);
	}
	return r;
}

Matrix2 rotation_matrix (double a) {
	Matrix2 m;
	m.m[0][0] = std::cos(a);
	m.m[0][1] = -std::sin(a);
	m.m[1][0] = std::sin(a);
	m.m[1][1] = std::cos(a);
	return m;
}
