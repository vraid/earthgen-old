#include "globe_renderer.h"
#include "../math/math_common.h"
#include "../math/vector2.h"
#include "../math/matrix3.h"
#include "../math/quaternion.h"
#include "../grid/grid.h"
#include "../terrain/terrain.h"
#include "planet_colors.h"
#include <iostream>
#include <math.h>

namespace earthgen {

Globe_renderer::Globe_renderer () : Planet_renderer () {
	reset_rotation();
}

void Globe_renderer::set_matrix () {
	glLoadIdentity();
	double x = width / default_size / scale;
	double y = height / default_size / scale;
	glOrtho(-x, x, -y, y, -2.0, 0.0);
}	

void Globe_renderer::draw_tile (const Tile* t, const Matrix3& m, const Color& color) {
	glColor3f(color);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(m*vector(t));
	for (const Corner* c : corners(t))
		glVertex3f(m*vector(c));
	glVertex3f(m*vector(corners(t)[0]));
	glEnd();
}

void Globe_renderer::draw (const Grid& grid, const Quaternion& q, const Planet_colors& colors) {
	set_matrix();
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	Matrix3 m = matrix3(rotation()*q);
	for (auto& t : tiles(grid)) {
		draw_tile(&t, m, colors.tiles[id(t)]);
	}
}

void Globe_renderer::change_scale (const Vector2&, double delta) {
	double min_scale = 0.6 * std::min(width, height) / default_size;
	double max_scale = 20;
	double new_scale = scale * delta;
	
	new_scale =
		new_scale < scale ?
			scale < min_scale ?
				scale :
				std::max(new_scale, min_scale) :
			new_scale;

	new_scale = std::min(new_scale, max_scale);

	scale = new_scale;
}

void Globe_renderer::mouse_dragged (const Vector2& delta) {
	longitude -= 0.0035 * delta.x() / scale;
	while (longitude > pi)
		longitude -= 2*pi;
	while (longitude <= -pi)
		longitude += 2*pi;
	
	latitude -= 0.0035 * delta.y() / scale;
	latitude = std::min(pi/2, latitude);
	latitude = std::max(-pi/2, latitude);
}

Vector3 Globe_renderer::to_coordinates (const Vector2& screen_position) const {
	Vector2 v = (screen_position - Vector2(width, height) * 0.5) * (2.0 / scale / default_size);

	if (squared_length(v) > 1.0)
		return Vector3();

	return conjugate(rotation()) * Vector3(v.x(), v.y(), sqrt(1.0-squared_length(v)));
}

void Globe_renderer::reset_rotation () {
	latitude = 0;
	longitude = 0;
}

Quaternion Globe_renderer::rotation () const {
	return latitude_rotation() * longitude_rotation() * axis_rotation();
}

Quaternion Globe_renderer::axis_rotation () const {
	return rotation_between(Vector3(1,0,0), Vector3(0,0,1)) * rotation_between(default_axis(), Vector3(0,1,0));
}

Quaternion Globe_renderer::longitude_rotation () const {
	return rotation_around(Vector3(0,1,0), -longitude);
}

Quaternion Globe_renderer::latitude_rotation () const {
	return rotation_around(Vector3(1,0,0), -latitude);
}

}
