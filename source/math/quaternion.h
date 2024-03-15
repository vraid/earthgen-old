#ifndef quaternion_h
#define quaternion_h

#include <array>

namespace earthgen {

class Vector3;
class Matrix3;

class Quaternion {
public:
	Quaternion ();
	Quaternion (double, double, double, double);
	
	Quaternion operator * (const Quaternion&) const;
	Vector3 operator * (const Vector3&) const;

	inline double at(int n) const { return values[n]; };

private:
	std::array<double, 4> values;
};

Quaternion rotation_around (const Vector3&, double);
Quaternion rotation_between (const Vector3&, const Vector3&);
Quaternion conjugate (const Quaternion&);
Vector3 vector (const Quaternion&);
Quaternion normal (const Quaternion&);
Matrix3 matrix3 (const Quaternion&);

}

#endif
