#ifndef vector2_h
#define vector2_h

class Vector2 {
public:
	Vector2 ();
	Vector2 (float, float);
	
	Vector2& operator = (const Vector2&);
	Vector2 operator + (const Vector2&) const;
	Vector2 operator - (const Vector2&) const;
	Vector2 operator * (double) const;
	
	float x;
	float y;
};

double length (const Vector2&);
double squared_length (const Vector2&);
double distance (const Vector2&, const Vector2&);
double squared_distance (const Vector2&, const Vector2&);
double angle (const Vector2&);

#endif
