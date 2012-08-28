#include "viewport.h"
#include "../projection/projection.h"
#include <algorithm>

Viewport::Viewport (int w, int h) {
	width = w;
	height = h;
	scale = min_scale (this);
}

void change_scale (Viewport* view, double s) {
	double ns = view->scale;
	if (s > 1) ns = std::min(s*view->scale, max_scale(view));
	else if (s < 1) ns = std::min(view->scale, std::max(s*view->scale, min_scale(view)));
	view->scale = ns;
}

void resize_viewport (Viewport* view, int width, int height) {
	view->width = width;
	view->height = height;
}

void set_center (Viewport* view, Vector2 v) {
	/* makes the map "stick" to the middle before changing center */
	double w = projection::hammer_width(0);
	double h = projection::hammer_height(0);
	if (v.x + w < w*min_scale(view)/view->scale) v.x = -w + w*min_scale(view)/view->scale;
	if (w - v.x < w*min_scale(view)/view->scale) v.x = w - w*min_scale(view)/view->scale;
	if (v.y + h < h*min_scale(view)/view->scale) v.y = -h + h*min_scale(view)/view->scale;
	if (h - v.y < h*min_scale(view)/view->scale) v.y = h - h*min_scale(view)/view->scale;
	view->center = v;
}

double max_scale (const Viewport* view) {
	return 20*view->width;
}

double min_scale (const Viewport* view) {
	return 0.75*std::min(1.0*view->width, 2.0*view->height)/projection::hammer_width(0.0);
}
