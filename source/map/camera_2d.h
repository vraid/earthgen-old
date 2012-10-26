#ifndef camera_2d_h
#define camera_2d_h

#include "../math/vector2.h"

class Camera_2d {
public:
	Camera_2d (int, int);
	~Camera_2d () {};

	double scale;
	int width;
	int height;
	Vector2 position;
	double tile_radius;
};

void change_scale (Camera_2d*, double);
void resize_camera (Camera_2d*, int, int);
void set_position (Camera_2d*, Vector2);
double max_scale (const Camera_2d*);
double min_scale (const Camera_2d*);

#endif
