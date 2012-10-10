#ifndef water_body_h
#define water_body_h

#include <set>

#define nullptr NULL

class Tile;
class Corner;

class Water_body {
public:
	Water_body() {
		outlet = nullptr;
		is_sea = true;
	}
	~Water_body() {};

	int id;
	std::set<const Tile*> tile;
	const Corner* outlet;
	bool is_sea;
};

#endif
