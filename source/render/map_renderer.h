#ifndef map_renderer_h
#define map_renderer_h

#include "planet_renderer.h"
#include "hammer_projection.h"

class Map_renderer : public Planet_renderer {
public:
	Map_renderer ();

	void set_matrix ();
	void draw_tile (int, const Colour&);
	void draw (const Planet&, const Quaternion&, const Planet_colours&);
	void change_scale (const Vector2&, double);
	void mouse_dragged (const Vector2&);
	Vector3 to_coordinates (const Vector2&) const;
	Vector2 max_offset () const;
	Vector2 min_offset () const;
	void clamp_offset ();
	double max_scale () const;
	double min_scale () const;
 	void update_geometry ();

	Vector2 screen_to_map_position (const Vector2&, double) const;
	Vector2 map_to_screen_position (const Vector2&, double) const;
	Vector2 map_offset () const;
	Vector2 invert_y (const Vector2&) const;

	Hammer_projection projection;
	Vector2 camera_position;
	bool geometry_updated;
};

#endif