#ifndef river_h
#define river_h

class Planet;
class Corner;
class Edge;

class River {
public:
	River () :
		source (nullptr), direction (nullptr), channel (nullptr) {}
	
	const Corner* source;
	const Corner* direction;
	const Edge* channel;
};

bool has_river (const Planet&, const Edge*);
const River river (const Planet&, const Edge*);
const River river (const Planet&, const Corner*);
const Corner* left_tributary (const Planet&, const River&);
const Corner* right_tributary (const Planet&, const River&);

#endif