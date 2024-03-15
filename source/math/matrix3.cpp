#include "matrix3.h"
#include "vector3.h"

#include <array>

namespace earthgen {

Matrix3::Matrix3 () :
	values ({{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}) {}

Matrix3::Matrix3 (const matrix3_value a) :
	values (a) {}

Matrix3 Matrix3::operator + (const Matrix3& m) const {
	auto sum = [=](int n, int k) { return at(n,k) + m.at(n, k); };
	auto row = [=](int n) { return matrix3_row {sum(n,0), sum(n,1), sum(n,2)}; };
	return Matrix3(matrix3_value {{row(0), row(1), row(2)}});
}

Vector3 Matrix3::operator * (const Vector3 &v) const {
	auto row = [=](int n) { return v.x()*at(n,0) + v.y()*at(n,1) + v.z()*at(n,2); };
	return Vector3(row(0), row(1), row(2));
}

}
