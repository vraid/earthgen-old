#include "util.h"
#include <ctime>
#include <iomanip>
#include <sstream>

QString randomAlpha (int length) {
	static char alpha[] =
	"abcdefghijklmnopqrstuvwxyz";
	std::string str;
	str.resize(length);
	srand(time(NULL));
	for (char& c : str) {
		c = alpha[rand()%26];
	}
	return QString::fromStdString(str);
}

QString randomAlphaNumeric (int length) {
	static char alphanum[] =
	"0123456789"
	"abcdefghijklmnopqrstuvwxyz";
	std::string str;
	str.resize(length);
	srand(time(NULL));
	for (char& c : str) {
		c = alphanum[rand()%36];
	}
	return QString::fromStdString(str);
}

QString string (const Vector3& v, int precision) {
	std::ostringstream buffer;
	buffer << std::fixed << std::setprecision(precision) << v.x << ", " << v.y << ", " << v.z;
	std::string s = buffer.str();
	return QString::fromStdString(s);
}

QString string (const Vector3& v) {
	return string(v, 2);
}