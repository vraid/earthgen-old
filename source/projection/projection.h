#ifndef projection_h
#define projection_h

#include <vector>
#include <map>
using std::vector;
using std::map;
#include "../math/vector2.h"
#include "../math/vector3.h"
#include "../math/quaternion.h"
class Planet;

class Projection {
public:
	Projection() {};
	~Projection() {};

	vector<Vector2> tile_center;
	vector<Vector2> tile_corner;
	vector<Vector2> north_center;
	vector<Vector2> south_center;
	
	int north_tile;
	int south_tile;
	int north_face;
	int south_face;

	vector<float> color;
	const Planet* p;
};

namespace projection {
	void init (const Planet*, Projection*);
	void reset_geometry (Projection*);
	void create_geometry (Projection*, const Quaternion&);
	void set_tile_geometry (Projection*, const Quaternion&, int);
	void set_north_tile (Projection*, const Quaternion&);
	void set_south_tile (Projection*, const Quaternion&);
	bool opposite_sides (const Vector2&, const Vector2&);
	Vector2 left_position (double, double);
	Vector2 right_position (double, double);
	void set_colors (Projection*);
	void color_topography (Projection*);
	Vector3 from_hammer (const Vector2&);
	Vector2 to_hammer (const Vector3&);
	Vector2 to_hammer (double, double);
	double hammer_width (double);
	double hammer_height (double);
}

#endif
