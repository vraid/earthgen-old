#ifndef vector2_h
#define vector2_h

class Vector2 {
public:
	Vector2();
	Vector2(double, double);
	~Vector2() {};

	Vector2& operator = (const Vector2&);
	Vector2 operator + (const Vector2&) const;
	
	double x;
	double y;
};

namespace vector2 {
}

#endif
