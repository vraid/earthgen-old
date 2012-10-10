#include "camera_2d.h"
#include "../projection/projection.h"
#include <algorithm>

Camera_2d::Camera_2d (int w, int h) {
	width = w;
	height = h;
	scale = min_scale (this);
}

void change_scale (Camera_2d* camera, double s) {
	double ns = camera->scale;
	if (s > 1) ns = std::min(s*camera->scale, max_scale(camera));
	else if (s < 1) ns = std::min(camera->scale, std::max(s*camera->scale, min_scale(camera)));
	camera->scale = ns;
}

void resize_camera (Camera_2d* camera, int width, int height) {
	camera->width = width;
	camera->height = height;
}

void set_position (Camera_2d* camera, Vector2 v) {
	/* makes the map "stick" to the middle before changing position */
	if (camera->scale <= min_scale(camera)) v = Vector2(0,0);
	else {
		double w = projection::hammer_width(0);
		double h = projection::hammer_height(0);
		if (v.x + w < w*min_scale(camera)/camera->scale) v.x = -w + w*min_scale(camera)/camera->scale;
		else if (w - v.x < w*min_scale(camera)/camera->scale) v.x = w - w*min_scale(camera)/camera->scale;
		if (v.y + h < h*min_scale(camera)/camera->scale) v.y = -h + h*min_scale(camera)/camera->scale;
		else if (h - v.y < h*min_scale(camera)/camera->scale) v.y = h - h*min_scale(camera)/camera->scale;
	}
	camera->position = v;
}

double max_scale (const Camera_2d* camera) {
	return 20*camera->width;
}

double min_scale (const Camera_2d* camera) {
	return 0.75*std::min(1.0*camera->width, 2.0*camera->height)/projection::hammer_width(0.0);
}
