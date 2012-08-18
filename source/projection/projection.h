#ifndef projection_h
#define projection_h

#include <vector>
#include <map>
using std::vector;
using std::map;
#include "../math/vector2.h"
class Vector3;
class Planet;

class Projection {
public:
	Projection() {};
	~Projection() {};

	vector<Vector2> tile;
	vector<Vector2> corner;
	map<int,Vector2> flipped_corner;
	vector<const Vector2*> polygon;
	int north_id;
	int south_id;
	Vector2 north_pole;
	Vector2 south_pole;
	vector<const Vector2*> north_tile;
	vector<const Vector2*> south_tile;

	const Planet* p;
};

namespace projection {
	void create_geometry (Projection*);
	bool flip (const Vector2&, const Vector2&);
	Vector3 from_hammer (const Vector2&);
	void init (const Planet*, Projection*);
	void set_colours (Projection*);
	Vector2 to_hammer (const Vector3&);
}

#endif
