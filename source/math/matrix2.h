#ifndef matrix2_h
#define matrix2_h

#include <vector>
class Vector2;

class Matrix2 {
public:
	Matrix2 ();
	Matrix2 (double[2][2]);
	
	Matrix2& operator = (const Matrix2&);
	Vector2 operator * (const Vector2&) const;
	std::vector<Vector2> operator * (const std::vector<Vector2>&) const;
	
	double m[2][2];
};

Matrix2 rotation_matrix (double);

#endif
