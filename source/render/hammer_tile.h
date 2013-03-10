#ifndef hammer_tile_h
#define hammer_tile_h

#include "../math/vector2.h"
class Tile;
class Matrix3;

class Hammer_tile {
public:
	Hammer_tile (const Tile*, const Matrix3&);
	
	Vector2 centre;
	Vector2 corners[6];
};

#endif