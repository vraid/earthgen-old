#ifndef wind_h
#define wind_h

class Wind {
public:
	Wind () :
		direction (0), speed (0) {}
	
	Wind& operator = (const Wind& w) {
		direction = w.direction;
		speed = w.speed;
		return *this;
	}

	float direction;
	float speed;
};

#endif
