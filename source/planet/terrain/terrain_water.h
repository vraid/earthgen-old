#ifndef terrain_water
#define terrain_water

namespace earthgen {

class Terrain_water {
public:
	Terrain_water () :
		surface (0), depth (0) {}

	float surface;
	float depth;
};

}

#endif
