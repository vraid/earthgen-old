#ifndef vector3_h
#define vector3_h

#include <array>

namespace earthgen {

class Vector3 {
public:
	Vector3 ();
	Vector3 (double, double, double);

	bool operator == (const Vector3&) const;
	bool operator != (const Vector3&) const;
	Vector3 operator + (const Vector3&) const;
	Vector3 operator - (const Vector3&) const;
	Vector3 operator * (double) const;
	
	inline double at (int n) const { return values[n]; }
	inline double x () const { return at(0); };
	inline double y () const { return at(1); };
	inline double z () const { return at(2); };

private:
	std::array<double, 3> values;
};

bool zero (const Vector3&);
bool parallel (const Vector3&, const Vector3&);
Vector3 normal (const Vector3&);
Vector3 cross_product (const Vector3&, const Vector3&);
double dot_product (const Vector3&, const Vector3&);
double length (const Vector3&);
double squared_length (const Vector3&);
double distance (const Vector3&, const Vector3&);
double squared_distance (const Vector3&, const Vector3&);
double angle (const Vector3&, const Vector3&);

}

#endif
