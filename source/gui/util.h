#ifndef util_h
#define util_h

#include <QString>
#include "../math/vector3.h"

QString randomAlpha (int length);
QString randomAlphaNumeric (int length);

QString string (const Vector3& v, int precision);

QString string (const Vector3& v);

#endif