#include "globe_renderer.h"
#include "../math/math_common.h"
#include "../math/vector2.h"
#include "../math/matrix3.h"
#include "../math/quaternion.h"
#include "../planet/planet.h"
#include "planet_colours.h"
#include <iostream>

Globe_renderer::Globe_renderer () : Planet_renderer () {
	reset_rotation();
	show_rivers = false;
}

void Globe_renderer::set_matrix () {
	glLoadIdentity();
	double x = width / default_size / scale;
	double y = height / default_size / scale;
	glOrtho(-x, x, -y, y, -2.0, 0.0);
}	

void Globe_renderer::draw_tile (const Tile* t, const Matrix3& m, const Colour& colour) {
	glColor3f(colour);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(m*vector(t));
	for (const Corner* c : corners(t))
		glVertex3f(m*vector(c));
	glVertex3f(m*vector(corners(t)[0]));
	glEnd();
}

void Globe_renderer::draw_river (const Tile* t, int edge, const Matrix3& m, const Colour& colour) {
	glColor3f(colour);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(m*(vector(nth_corner(t, edge)) + (vector(nth_corner(t, edge-1)) - vector(nth_corner(t, edge)))*0.1));
	glVertex3f(m*vector(nth_corner(t, edge)));
	glVertex3f(m*vector(nth_corner(t, edge+1)));
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(m*vector(nth_corner(t, edge+1)));
	glVertex3f(m*(vector(nth_corner(t, edge+1)) + (vector(nth_corner(t, edge+2)) - vector(nth_corner(t, edge+1)))*0.1));
	glVertex3f(m*(vector(nth_corner(t, edge)) + (vector(nth_corner(t, edge-1)) - vector(nth_corner(t, edge)))*0.1));
	glEnd();

	/*
	glColor3f(colour);
	glBegin(GL_TRIANGLE_FAN);
	auto& v = river_segment(t, edge);
	for (int i=0; i<4; i++)
		glVertex3f(m*v[i]);
	glEnd();
	*/
}

void Globe_renderer::draw (const Planet& planet, const Quaternion& q, const Planet_colours& colours) {
	set_matrix();
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	Matrix3 m = matrix3(rotation()*q);
	for (auto& t : tiles(planet)) {
		draw_tile(&t, m, colours.tiles[id(t)]);
	}

	if (show_rivers)
		for (auto& t : tiles(planet))
			if (is_land(nth_tile(terrain(planet), id(t)))) {
				for (int k=0; k<edge_count(&t); k++) {
					auto e = nth_edge(t, k);
					if (has_river(planet, e)) {
						River r = river(planet, e);
						if (left_tributary(planet, r) || right_tributary(planet, r))
							draw_river(&t, k, m, Colour(0.04, 0.14, 0.72));
					}
				}
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
	longitude -= 0.0035 * delta.x / scale;
	while (longitude > pi)
		longitude -= 2*pi;
	while (longitude <= -pi)
		longitude += 2*pi;
	
	latitude -= 0.0035 * delta.y / scale;
	latitude = std::min(pi/2, latitude);
	latitude = std::max(-pi/2, latitude);
}

Vector3 Globe_renderer::to_coordinates (const Vector2& screen_position) const {
	Vector2 v = (screen_position - Vector2(width, height) * 0.5) * (2.0 / scale / default_size);

	if (squared_length(v) > 1.0)
		return Vector3();

	return conjugate(rotation()) * Vector3(v.x, v.y, sqrt(1.0-squared_length(v)));
}

void Globe_renderer::reset_rotation () {
	latitude = 0;
	longitude = 0;
}

Quaternion Globe_renderer::rotation () const {
	return latitude_rotation() * longitude_rotation() * axis_rotation();
}

Quaternion Globe_renderer::axis_rotation () const {
	Quaternion q = Quaternion(default_axis(), Vector3(0,1,0));
	return Quaternion(Vector3(1,0,0), Vector3(0,0,1)) * q;
}

Quaternion Globe_renderer::longitude_rotation () const {
	return Quaternion(Vector3(0,1,0), -longitude);
}

Quaternion Globe_renderer::latitude_rotation () const {
	return Quaternion(Vector3(1,0,0), -latitude);
}
