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
	int north_id;
	int south_id;
	vector<Vector2> north_tile;
	vector<Vector2> south_tile;

	vector<float> color;
	Planet* p;
};

namespace projection {
	void create_geometry (Projection*);
	bool flip (const Vector2&, const Vector2&);
	bool flip (const Vector3&, const Vector3&);
	Vector3 from_hammer (const Vector2&);
	void init (Planet*, Projection*);
	void set_colors (Projection*);
	Vector2 to_hammer (const Vector3&);
	double hammer_width (double);
	double hammer_height (double);
}

#endif
