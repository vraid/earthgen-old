#include "map_renderer.h"
#include "planet_colours.h"
#include "../planet/planet.h"
#include "../math/quaternion.h"

Map_renderer::Map_renderer () : Planet_renderer () {
	geometry_updated = false;
	scale = min_scale();
}

void Map_renderer::set_matrix () {
	glLoadIdentity();
	Vector2 bottom_left = screen_to_map_position(Vector2(0,height), scale) + map_offset();
	Vector2 top_right = screen_to_map_position(Vector2(width, 0), scale) + map_offset();
	glOrtho(bottom_left.x, top_right.x, bottom_left.y, top_right.y, -2.0, 0.0);
}

void Map_renderer::draw_tile (int i, const Colour& colour) {
	glColor3f(colour);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(projection.tiles[i].centre);
	for (auto& c : projection.tiles[i].corners)
		glVertex2f(c);
	glVertex2f(projection.tiles[i].corners[0]);
	glEnd();
}

void Map_renderer::draw (const Planet& planet, const Quaternion& q, const Planet_colours& colours) {
	if (!geometry_updated) {
		create_geometry(projection, planet, q);
		geometry_updated = true;
	}

	set_matrix();
	for (int i=0; i<tile_count(planet); i++)
		draw_tile(i, colours.tiles[i]);
}

void Map_renderer::change_scale (const Vector2& screen_position, double delta) {
	double new_scale = scale * delta;
	
	new_scale =
		new_scale < scale ?
			scale < min_scale() ?
				scale :
				std::max(new_scale, min_scale()) :
				new_scale;
	
	new_scale = std::min(new_scale, max_scale());
	
	camera_position = camera_position + screen_to_map_position(screen_position, new_scale) - screen_to_map_position(screen_position, scale);
	scale = new_scale;
	clamp_offset();
}

void Map_renderer::mouse_dragged (const Vector2& delta) {
	camera_position = screen_to_map_position(delta + map_to_screen_position(camera_position, scale), scale);
	clamp_offset();
}

Vector3 Map_renderer::to_coordinates (const Vector2& screen_position) const {
	Vector2 v = screen_to_map_position(screen_position, scale) + map_offset();
	
	if (squared_length(Vector2(v.x/hammer_width(), v.y/hammer_height())) > 1.0)
		return Vector3();
	return from_hammer(v);
}

Vector2 Map_renderer::max_offset () const {
	return Vector2(hammer_width(), hammer_height())*(1.0 - min_scale()/scale);
}

Vector2 Map_renderer::min_offset () const {
	return Vector2(hammer_width(), hammer_height())*(min_scale()/scale - 1.0);
}

void Map_renderer::clamp_offset () {
	/* makes the map "stick" to the middle before changing position */
	Vector2 v = camera_position;
	if (scale <= min_scale()) v = Vector2(0,0);
	else {
		double w = hammer_width();
		double h = hammer_height();
		if (v.x + w < w*min_scale()/scale)
			v.x = -w + w*min_scale()/scale;
		else if (w - v.x < w*min_scale()/scale)
			v.x = w - w*min_scale()/scale;
		if (v.y + h < h*min_scale()/scale)
			v.y = -h + h*min_scale()/scale;
		else if (h - v.y < h*min_scale()/scale)
			v.y = h - h*min_scale()/scale;
	}
	camera_position = v;
}

double Map_renderer::max_scale () const {
	return 20*400;
}

double Map_renderer::min_scale () const {
	return 0.85*std::min(0.5*width, 1.0*height)/hammer_width();
}

void Map_renderer::update_geometry () {
	clear(projection);
	geometry_updated = false;
}

Vector2 Map_renderer::screen_to_map_position (const Vector2& screen_position, double scale) const {
	return invert_y(screen_position - Vector2(0.5*width, 0.5*height)) * (1.0 / scale);
}

Vector2 Map_renderer::map_to_screen_position (const Vector2& map_position, double scale) const {
	return invert_y(map_position * scale) + Vector2(0.5*width, 0.5*height);
}

Vector2 Map_renderer::map_offset () const {
	return Vector2() - camera_position;
}

Vector2 Map_renderer::invert_y (const Vector2& v) const {
	return Vector2(v.x, -v.y);
}