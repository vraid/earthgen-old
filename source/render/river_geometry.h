#ifndef river_geometry_h
#define river_geometry_h

#include "../math/vector3.h"
#include <deque>
#include <vector>

struct River_segment {
	Vector3 v[4];
};

class River_geometry {
public:
	River_geometry () {}

	void create (const Planet&);

	std::deque<River_segment> segments;
	std::vector<int> edge_segment_id;
};

#endif