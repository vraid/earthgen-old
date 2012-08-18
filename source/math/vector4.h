#ifndef vector4_h
#define vector4_h

class Vector4 {
public:
	Vector4 ();
	Vector4 (double, double, double, double);
	~Vector4 () {};

	Vector4& operator = (const Vector4&);

	double x;
	double y;
	double z;
	double w;
};

#endif
