#ifndef matrix3_h
#define matrix3_h

#include <array>

namespace earthgen {

typedef std::array<double, 3> matrix3_row;
typedef std::array<matrix3_row, 3> matrix3_value;

class Vector3;

class Matrix3 {
public:
	Matrix3 ();
	Matrix3 (const matrix3_value);

	Matrix3 operator + (const Matrix3&) const;
	Vector3 operator * (const Vector3&) const;

	double at (int n, int k) const { return values[n][k]; };

private:
	matrix3_value values;
};

}

#endif
