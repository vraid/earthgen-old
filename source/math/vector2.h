#ifndef vector2_h
#define vector2_h

#include <array>

namespace earthgen {

class Vector2 {
public:
	Vector2 ();
	Vector2 (double, double);
	
	Vector2 operator + (const Vector2&) const;
	Vector2 operator - (const Vector2&) const;
	Vector2 operator * (double) const;

	inline double at (int n) const { return values[n]; }
	inline double x () const { return at(0); };
	inline double y () const { return at(1); };

private:
	std::array<double, 2> values;
};

double length (const Vector2&);
double squared_length (const Vector2&);
double distance (const Vector2&, const Vector2&);
double squared_distance (const Vector2&, const Vector2&);
double angle (const Vector2&);

}

#endif
