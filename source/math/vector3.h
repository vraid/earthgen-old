#ifndef vector3_h
#define vector3_h

class Vector3 {
public:
	Vector3 ();
	Vector3 (float, float, float);

	bool operator == (const Vector3&) const;
	bool operator != (const Vector3&) const;
	Vector3& operator = (const Vector3&);
	Vector3 operator + (const Vector3&) const;
	Vector3 operator - (const Vector3&) const;
	Vector3 operator * (double) const;
	
	float x;
	float y;
	float z;
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

#endif
