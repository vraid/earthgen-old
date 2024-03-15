#ifndef planet_render_data
#define planet_render_data

namespace earthgen {

class Planet;

class Planet_render_data {
public:
	Planet_render_data () {}
	~Planet_render_data () {}

	const Planet* planet;
};

}

#endif
