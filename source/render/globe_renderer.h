#ifndef globe_renderer_h
#define globe_renderer_h

#include "planet_renderer.h"

namespace earthgen {

class Vector2;
class Quaterion;
class Matrix3;
class Tile;
class Planet;

class Globe_renderer : public Planet_renderer {
public:
	Globe_renderer ();

	void set_matrix ();
	void draw_tile (const Tile*, const Matrix3&, const Color&);
	void draw (const Grid&, const Quaternion&, const Planet_colors&);
	void change_scale (const Vector2&, double);
	void mouse_dragged (const Vector2&);
	Vector3 to_coordinates (const Vector2&) const;
	void reset_rotation ();
	Quaternion rotation () const;
	Quaternion axis_rotation () const;
	Quaternion longitude_rotation () const;
	Quaternion latitude_rotation () const;

	double latitude;
	double longitude;
};

}

#endif
