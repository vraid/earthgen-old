#ifndef quaternion_h
#define quaternion_h

class Vector3;
class Matrix3;

class Quaternion {
public:
	Quaternion ();
	Quaternion (const Vector3&, double);
	Quaternion (const Vector3&, const Vector3&);
	Quaternion (double, double, double, double);
	
	Quaternion& operator = (const Quaternion&);
	Quaternion operator * (const Quaternion&) const;
	Vector3 operator * (const Vector3&) const;
	
	double a;
	double i;
	double j;
	double k;
};

Quaternion conjugate (const Quaternion&);
Vector3 vector (const Quaternion&);
Quaternion normal (const Quaternion&);
Matrix3 matrix3 (const Quaternion&);

#endif
