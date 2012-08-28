#ifndef viewport_h
#define viewport_h

#include "../math/vector2.h"

class Viewport {
public:
	Viewport (int, int);
	~Viewport () {};

	double scale;
	int width;
	int height;
	Vector2 center;
	double tile_radius;
};

void change_scale (Viewport*, double);
void resize_viewport (Viewport*, int, int);
void set_center (Viewport*, Vector2);
double max_scale (const Viewport*);
double min_scale (const Viewport*);

#endif
