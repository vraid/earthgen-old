#ifndef terrain_corner_h
#define terrain_corner_h

class Corner;

class Terrain_corner {
public:
	Terrain_corner() {
		elevation = 0;
		stream_direction = nullptr;
	}
	~Terrain_corner() {};

	double elevation;

	bool is_coast;
	const Corner* stream_direction;
};

#endif
