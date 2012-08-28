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
	
	float x;
	float y;
};

namespace vector2 {
}

#endif
