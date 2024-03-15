#ifndef matrix2_h
#define matrix2_h

#include <array>
#include <vector>

namespace earthgen {

typedef std::array<double, 2> matrix2_row;
typedef std::array<matrix2_row, 2> matrix2_value;

class Vector2;

class Matrix2 {
public:
	Matrix2 ();
	Matrix2 (const matrix2_value);

	Vector2 operator * (const Vector2&) const;
	std::vector<Vector2> operator * (const std::vector<Vector2>&) const;

	inline double at (int n, int k) const { return values[n][k]; };

private:
	matrix2_value values;
};

Matrix2 rotation_matrix (double);

}

#endif
