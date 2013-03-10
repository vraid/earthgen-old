#include "matrix3.h"
#include "vector3.h"

Matrix3::Matrix3 () {
	for (int i=0; i<3; i++) {
		for (int k=0; k<3; k++) {
			if (i == k)
				m[i][k] = 1;
			else
				m[i][k] = 0;
		}
	}
}

Matrix3::Matrix3 (double a[3][3]) {
	for (int i=0; i<3; i++)
		for (int k=0; k<3; k++)
			m[i][k] = a[i][k];
}

Matrix3& Matrix3::operator = (const Matrix3 &n) {
	for (int i=0; i<3; i++)
		for (int k=0; k<3; k++)
			m[i][k] = n.m[i][k];
	return *this;
}

Vector3 Matrix3::operator * (const Vector3 &v) const {
	return Vector3
		(v.x*m[0][0] + v.y*m[0][1] + v.z*m[0][2],
		 v.x*m[1][0] + v.y*m[1][1] + v.z*m[1][2],
		 v.x*m[2][0] + v.y*m[2][1] + v.z*m[2][2]);
}

