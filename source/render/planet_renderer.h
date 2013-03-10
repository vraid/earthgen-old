#ifndef planet_renderer_h
#define planet_renderer_h

#include <QGLWidget>
#include "../math/vector2.h"
#include "../math/vector3.h"
#include "colour.h"
class Planet;
class Quaternion;

class Planet_colours;

class Planet_renderer {
public:
	Planet_renderer ();

	void set_viewport_size (int, int);
	virtual void change_scale (const Vector2&, double);
	virtual void mouse_dragged (const Vector2&);
	virtual Vector3 to_coordinates (const Vector2&) const;
	virtual void draw (const Planet&, const Quaternion&, const Planet_colours&) = 0;

	int width;
	int height;
	double default_size;
	double scale;
};

inline void glVertex2f (const Vector2& v) {glVertex2f(v.x, v.y);}
inline void glVertex3f (const Vector3& v) {glVertex3f(v.x, v.y, v.z);}
inline void glColor3f (const Colour& c) {glColor3f(c.r, c.g, c.b);}

#endif