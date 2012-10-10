#ifndef terrain_corner_h
#define terrain_corner_h

class Corner;

class Terrain_corner {
public:
	Terrain_corner() {
		elevation = 0;
		sea_distance = 0;
		river_direction = nullptr;
	}
	~Terrain_corner() {};

	float elevation;

	bool is_land;
	bool is_water;
	bool is_coast;
	int sea_distance;
	const Corner* river_direction;
};

#endif
