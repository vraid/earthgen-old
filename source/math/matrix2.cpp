#include "matrix2.h"
#include "vector2.h"
#include <cmath>
#include <algorithm>

namespace earthgen {

Matrix2::Matrix2() :
	values ({{{1, 0}, {0, 1}}}) {}

Matrix2::Matrix2(const matrix2_value a) :
	values (a) {}

Vector2 Matrix2::operator * (const Vector2& v) const {
	auto row = [=](int n) { return v.x()*at(n,0) + v.y()*at(n,1); };
	return Vector2(row(0), row(1));
}

std::vector<Vector2> Matrix2::operator * (const std::vector<Vector2>& vectors) const {
	std::vector<Vector2> result;
	std::transform(vectors.begin(), vectors.end(), std::back_inserter(result), [=](const Vector2 v) { return *this * v; });
	return result;
}

Matrix2 rotation_matrix (double a) {
	return Matrix2(
		{{{std::cos(a), -std::sin(a)},
		  {std::sin(a), std::cos(a)}}});
}

}
