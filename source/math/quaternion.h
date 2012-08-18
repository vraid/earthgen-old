#ifndef quaternion_h
#define quaternion_h

class Vector3;
class Matrix3;

class Quaternion {
public:
	Quaternion();
	Quaternion(double, const Vector3&);
	Quaternion(const Vector3&, const Vector3&);
	Quaternion(double, double, double, double);
	~Quaternion() {};

	Quaternion& operator = (const Quaternion&);
	Quaternion operator * (const Quaternion&) const;
	Vector3 operator * (const Vector3&) const;

	double w;
	double x;
	double y;
	double z;
};

namespace quaternion {
	Quaternion conjugate (const Quaternion&);
	Quaternion normal (const Quaternion&);
	Vector3 vector (const Quaternion&);
	Matrix3 matrix (const Quaternion&);
	Vector3 vector (const Quaternion&);
}

#endif
