#ifndef map_projection_h
#define map_projection_h

#include <deque>
#include <vector>

class Map_projection_tile {
public:
	Map_projection_tile () {
		corners.resize(6);
	}

	Vector3 center;
	std::vector<Vector3> corners;
};

class Map_projection {
public:
	Map_projection () {}

	std::deque<Map_projection_tile> tiles;
};

const std::deque<Map_projection_tile>& tiles (const Map_projection* p) {return p->tiles;}

void clear_map_projection ..
void init_map_projection ..
void create_map_projection ..

#endif