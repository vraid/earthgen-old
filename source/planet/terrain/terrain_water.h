#ifndef terrain_water_h
#define terrain_water_h

class Water_body;

class Terrain_water {
public:
	Terrain_water() {
		depth = 0;
		level = 0;
		body = -1;
	}
	~Terrain_water() {};

	double depth;
	double level;
	int body;
};

#endif
