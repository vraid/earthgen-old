#ifndef empty_renderer_h
#define empty_renderer_h

#include "planet_renderer.h"

class Empty_renderer : public Planet_renderer {
public:
	Empty_renderer () {}
	
	void change_scale (const Vector2&, double) {}
	void mouse_dragged (const Vector2&) {}
	Vector3 to_coordinates (const Vector2&) const {return Vector3();}
	void draw (const Planet&, const Quaternion&, const Planet_colours&) {}
};

#endif