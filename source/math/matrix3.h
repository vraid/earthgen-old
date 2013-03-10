#ifndef matrix3_h
#define matrix3_h

class Vector3;

class Matrix3 {
public:
	Matrix3 ();
	Matrix3 (double[3][3]);
	~Matrix3 () {}
	
	Matrix3& operator = (const Matrix3&);
	Vector3 operator * (const Vector3&) const;
	
	double m[3][3];
};

#endif
