#ifndef wind_h
#define wind_h

class Wind {
public:
	Wind () {
		direction = 0.0;
		speed = 0.0;
	}
	~Wind () {};

	float direction;
	float speed;
};

#endif
