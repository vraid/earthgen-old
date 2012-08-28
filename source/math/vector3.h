#ifndef vector3_h
#define vector3_h

class Vector3 {
public:
	Vector3();
	Vector3(double, double, double);
	~Vector3() {};

	Vector3& operator = (const Vector3&);
	Vector3 operator + (const Vector3&) const;
	Vector3 operator * (double) const;

	float x;
	float y;
	float z;
};

namespace vector3 {
	Vector3 cross_product (const Vector3&, const Vector3&);
	double distance (const Vector3&, const Vector3&);
	double distance_square (const Vector3&, const Vector3&);
	double dot_product (const Vector3&, const Vector3&);
	double length (const Vector3&);
	double length_square (const Vector3&);
	Vector3 normal (const Vector3&);
}

#endif
