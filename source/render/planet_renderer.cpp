#include "planet_renderer.h"

Planet_renderer::Planet_renderer () {
	default_size = 600;
	width = 600;
	height = 600;
	scale = 1;
}

void Planet_renderer::set_viewport_size (int w, int h) {
	width = w;
	height = h;
}

void Planet_renderer::change_scale (const Vector2&, double delta) {
	scale *= delta;
}

void Planet_renderer::mouse_dragged (const Vector2&) {}

Vector3 Planet_renderer::to_coordinates (const Vector2&) const {
	return Vector3();
}
