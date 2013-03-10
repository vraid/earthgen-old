#ifndef hammer_projection_h
#define hammer_projection_h

#include "hammer_tile.h"
#include <deque>
class Vector2;
class Vector3;
class Quaternion;
class Planet;

class Hammer_projection {
public:
	Hammer_projection () {}

	std::deque<Hammer_tile> tiles;
};

void clear (Hammer_projection&);
void create_geometry (Hammer_projection&, const Planet&, const Quaternion&);

Vector3 from_hammer (const Vector2&);
Vector2 to_hammer (const Vector3&);
Vector2 to_hammer (double latitude, double longitude);

double hammer_width ();
double hammer_height ();

#endif