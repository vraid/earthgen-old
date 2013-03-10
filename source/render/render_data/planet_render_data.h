#ifndef planet_render_data
#define planet_render_data

class Planet;
class River_geometry;

class Planet_render_data {
public:
	Planet_render_data () {}
	~Planet_render_data () {}

	const Planet* planet;
	River_geometry* river_geometry;
};

#endif