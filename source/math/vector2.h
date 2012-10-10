#ifndef vector2_h
#define vector2_h

class Vector2 {
public:
	Vector2();
	Vector2(double, double);
	~Vector2() {};

	Vector2& operator = (const Vector2&);
	Vector2 operator + (const Vector2&) const;
	Vector2 operator - (const Vector2&) const;
	Vector2 operator * (double) const;
	Vector2 operator / (double) const;
	
	float x;
	float y;
};

namespace vector2 {
	double angle (const Vector2&);
	double length (const Vector2&);
	Vector2 rotate (const Vector2&, double);
}

#endif
